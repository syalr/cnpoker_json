#include "GameTable.h"
#include "GameServer.h"

UINT GameTable::m_maxCallBanks = 4;

GameTable::GameTable()
{
    memset( this, 0x0, sizeof(this) );
}

GameTable::~GameTable()
{

}

int myRandom(BYTE i)
{
	return rand() % i;
}

int GameTable::JoinGame( GameUser * pUser )
{
    if ( pUser != NULL )
    {
        if ( m_bySatus[0] == eGT_EMPTY ) {
            m_pGameUser[0] = pUser;
            pUser->JoinGame(m_uiTableIndex, 0);
            m_bySatus[0] = eGT_WAITING;
            return 0;
        }
        if ( m_bySatus[1] == eGT_EMPTY ) {
            m_pGameUser[1] = pUser;
            pUser->JoinGame(m_uiTableIndex, 1);
            m_bySatus[1] = eGT_WAITING;
            return 1;
        }
        if ( m_bySatus[2] == eGT_EMPTY ) {
            m_pGameUser[2] = pUser;
            pUser->JoinGame(m_uiTableIndex, 2);
            m_bySatus[2] = eGT_WAITING;
            return 2;
        }
    }
    return -1;
}

int GameTable::QuitGame( GameUser * pUser )
{
    BYTE _bySeat =  pUser->m_bySeat;

    if ( _bySeat>=0 && _bySeat<3 )
    {
        if ( m_bySatus[_bySeat] != eGT_EMPTY ) {
            m_pGameUser[_bySeat] = NULL;
            m_bySatus[_bySeat] = eGT_EMPTY;
            pUser->Clear();
            return TRUE;
        }
    }
    return FALSE;
}

int GameTable::IsEmpty()
{
    if ( m_bySatus[0] == eGT_EMPTY ) {
        if ( m_bySatus[1] == eGT_EMPTY ) {
            if ( m_bySatus[2] == eGT_EMPTY ) {
                return TRUE;
            }
        }
    }
    return FALSE;
}


int GameTable::StartGame()
{
    if ( m_bySatus[0] == eGT_STARTGAME ) {
        if ( m_bySatus[1] == eGT_STARTGAME ) {
            if ( m_bySatus[2] == eGT_STARTGAME ) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int GameTable::Shuffle()
{
	srand( (unsigned)time(NULL) );

	vector<BYTE> vecCards;
	vecCards.reserve(CNPOKER_CARD_LEN_1); // 54
	for(BYTE i=0; i<CNPOKER_CARD_LEN_1; ++i) {
		vecCards.push_back(i);
	}

	std::random_shuffle( vecCards.begin(), vecCards.end(), myRandom ); // 乱序

	BYTE * pMove = m_byAllCards;
	pMove[ vecCards[0] ] = CNPOKER_HOLE; // m_byAllCards[4] = 3
	pMove[ vecCards[1] ] = CNPOKER_HOLE; // m_byAllCards[51] = 3
	pMove[ vecCards[2] ] = CNPOKER_HOLE; // m_byAllCards[11] = 3

	// 把额外那三张牌给保存下来
	BYTE * pExtraCards = m_byExtraCards;
	*pExtraCards++ = vecCards[0]; // 也就是额外那3张牌是 4， 51， 11
	*pExtraCards++ = vecCards[1];
	*pExtraCards   = vecCards[2];

	// 把牌分成3份
	for(BYTE i=3; i<54; ++i) {
		pMove[ vecCards[i] ] = i%3; // 如: m_byAllCards[15] = 0; m_byAllCards[24] = 1; m_byAllCards[35] = 2; // 第15张是玩家0的牌,24张是玩家1的牌...
	}
}

int GameTable::Alloc()
{
    GameUser * pUser;
	BYTE     * pMove = m_byAllCards;

	for(int i=0; i<3; ++i)
	{
		if (i != 0) //
		{
			GameUser * pUser = m_pGameUser[i];
			if ( pUser == NULL ) {
                return FALSE;
            }
		}

		pUser->Clear();
		pUser->SetCards(m_byAllCards, CNPOKER_CARD_LEN_1);
	}

    return TRUE;
}

// 抢庄
int GameTable::GetBank( BYTE _bySeat, BYTE _getBank )
{
    if ( _getBank == TRUE )
    {
        m_calledBanks ++;
        if ( m_calledBanks == GameTable::m_maxCallBanks ) {
            return TRUE;
        }

            if ( m_bySatus[0] == eGT_STARTGAME ) {
            if ( m_bySatus[1] == eGT_STARTGAME ) {
                if ( m_bySatus[2] == eGT_STARTGAME ) {
                    return TRUE;
                }
            }
        }

        m_bySatus [_bySeat] = eGT_GETBANK;
    }
    return TRUE;
}

int GameTable::Discards(BYTE * pCards, unsigned int uiSize, BYTE _bySeat)
{
    printf("[GameTable::Discards] : Table Size = %d\n", uiSize);

    // == 不是第一次出牌；
    if (m_byDiscardCurr != -1) {

        // == 即出牌并没有作弊
	    if ( m_byDiscardCurr != _bySeat ) {
            return FALSE;
        }
	}

	int nRet = PH_0;
	char cThanValue1, cThanCount1, cThanValue2, cThanCount2;
	int eType1 = PH_0, eType2 = PH_0;

	// 判断出牌是否符合逻辑
	eType1 = Poker::Pick(pCards, uiSize, cThanValue1, cThanCount1);
	if ( eType1 == PH_0 ) {
		return FALSE;
	}

	// 如果 最后一个有牌权的人 不等于 上一次出牌的人， 则需要对出牌先做判断
	if ( m_byDiscardLast != m_byDiscardCurr ) {
		// 与之前打的牌比较
		eType2 		= m_ePkType;
		cThanValue2 = m_byCmpValue;
		cThanCount2 = m_byCmpCount;

		int nResult = Poker::Than( (ePK_TYPE)eType1, cThanValue1, cThanCount1, (ePK_TYPE)eType2, cThanValue2, cThanCount2 );
		if ( nResult == PH_0 ) {
			return FALSE;
		}
	}

	// 此时可以直接出牌了
	// 将打出的牌 1.自己手上的牌 设为 -1;  2.桌子上已打出的牌 设为 -1
	GameUser * pUser = m_pGameUser[m_byDiscardCurr];
    if ( pUser != NULL )
	{
	    int nBack = pUser->FigureOutDiscards(pCards, uiSize); // 传入 玩家打出的牌数组 和 个数
        if ( nBack == -1) {
            return FALSE;
        }
	}

	// 记录打出的最大的牌 及 张数 及 类型
	m_ePkType = (ePK_TYPE)nRet;
	m_byCmpValue = cThanValue1;
	m_byCmpCount = cThanCount1;

	// 判断是第一次出牌，即初始化
	if (m_byDiscardCurr == -1) {
		m_byDiscardCurr = _bySeat; // 第一次出牌
		m_byDiscardLast = _bySeat;
	}

	return TRUE;
}

int GameTable::Pass(BYTE _bySeat)
{
    if ( _bySeat >= 0 && _bySeat < 3)
    {
        int index = (_bySeat + 1) % 3;
        if ( m_bySatus[index] == eGT_PASS )
        {
            index = (index + 1) % 3;
            if ( m_bySatus[index] == eGT_PASS )
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

int GameTable::IsWoned()
{
    if ( m_byDiscardCurr>=0 && m_byDiscardCurr<3 )
    {
        int index = (m_byDiscardCurr + 1) % 3;
        if ( m_bySatus[index] == eGT_PASS )
        {
            index = (index + 1) % 3;
            if ( m_bySatus[index] == eGT_PASS )
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int GameTable::IsEndGame()
{
    GameUser * pUser = m_pGameUser[m_byDiscardCurr];
    if ( pUser != NULL )
	{
	    int rets = pUser->GetCount(); // 传入 玩家打出的牌数组 和 个数
        if ( rets == 0) {
            return TRUE;
        }
	}
	return FALSE;
}

int GameTable::NextUser()
{
    BYTE idx = (m_byDiscardCurr + 1) % 3;

    GameUser * pUser = m_pGameUser[idx];
    if ( pUser == NULL ) {
        return FALSE;
    }

    m_byDiscardCurr = idx;
    return TRUE;
}

int GameTable::Settlement()
{

    return TRUE;
}

int GameTable::ClearTable()
{

}

int GameTable::ClearGame()
{
    memset(m_byAllCards, 0x0,CNPOKER_CARD_LEN_1);
    memset(m_byDiscards, 0x0,CNPOKER_CARD_LEN_1);

	m_byDiscardCurr = -1;       // 现在出牌的坐位
	m_byDiscardLast = -1;       // 最后出牌的坐位

	m_bySatus[0] = eGT_EMPTY;
	m_bySatus[1] = eGT_EMPTY;
	m_bySatus[2] = eGT_EMPTY;

    if ( m_pGameUser[0] != NULL ) {
        m_bySatus[0] = eGT_WAITING;
    }
    if ( m_pGameUser[1] != NULL ) {
        m_bySatus[1] = eGT_WAITING;
    }
    if ( m_pGameUser[2] != NULL ) {
        m_bySatus[2] = eGT_WAITING;
    }

    m_calledBanks =  0;
    m_dwLandlord  = -1;
}


// 向所有人发送Json数据
int GameTable::Broadcast(BYTE * msg, WORD wSize)
{
    /*
    MSG_BASE_FORWARD * msg2 = ( MSG_BASE_FORWARD * ) msg;

    msg2->m_dwUserID = m_uiUserKey[0];
    g_GameServer->SendToAgentServer( (BYTE*) &msg, wSize );

    msg2->m_dwUserID = m_uiUserKey[1];
    g_GameServer->SendToAgentServer( (BYTE*) &msg, wSize );

    msg2->m_dwUserID = m_uiUserKey[2];
    g_GameServer->SendToAgentServer( (BYTE*) &msg, wSize );
    */
}
