#include "GameUser.h"
#include "GameServer.h"

/*******************************/
GameUser::GameUser()
{

}

GameUser::~GameUser()
{

}

int GameUser::Clear()
{

}

int GameUser::JoinGame(WORD _table, BYTE _seat)
{
    m_byRemove  = FALSE;
    m_wTable    = _table;
    m_bySeat    = _seat;
}

void GameUser::CallBank()
{

}

int GameUser::FigureOutDiscards(BYTE * pCards, unsigned int uiSize)
{
	unsigned char tCard;

	// 判断手上是否有打出的这些牌，有，则对应位置 设为 -1
	for ( int i=0; i<uiSize; ++i )
	{
		tCard = pCards[i]; // 13, 16, 18

		if ( tCard > 0 && tCard < CNPOKER_CARD_LEN_1 ) // 小于54
		{
			if ( m_szCards[tCard] == eGU_EMPTY ) {
                return FALSE;
            }
            m_szCards[tCard] = eGU_EMPTY;
		}
	}

    m_byCCount = m_byCCount - uiSize;

	return TRUE;
}

int GameUser::SetCards(BYTE *poker, WORD wSize)
{
    m_byCCount = 0;
    if ( (poker!=NULL) && (wSize<CNPOKER_CARD_LEN_1) )
    {
        memset( m_szCards, eGU_EMPTY, sizeof(m_szCards) );

        for(BYTE c=0; c<wSize; ++c)
        {
            if ( *poker == m_bySeat )
            {
                m_szCards[c] = eGU_OWNED;
                m_byCCount++;
            }
        }
    }
}

