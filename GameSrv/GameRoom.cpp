#include "GameRoom.h"
#include "GameFactory.h"
#include "GameUserList.h"
#include "GameTableList.h"

GameRoom g_pGameRoom;

/*******************************/
GameRoom::GameRoom()
{

}

GameRoom::~GameRoom()
{

}

int GameRoom::Create(WORD wTableSize, WORD wUserSize)
{
    memset ( m_pActiveTable, 0x0, sizeof(m_pActiveTable) );
    memset ( m_pActiveUser,  0x0, sizeof(m_pActiveUser) );

    GameFactory * pFactory = GameFactory::Instance();

    GameTable * pGameTable = NULL;
    for( DWORD i = 0; i < wTableSize; ++i )
	{
		pGameTable = pFactory->AllocGameTable();
		pGameTable->m_uiTableIndex = i;
		if ( pGameTable !=NULL ) {
            m_pEmptyTableList.push_back(pGameTable);
        }
	}

    GameUser * pGameUser = NULL;
    for( DWORD i = 0; i < wUserSize; ++i )
	{
		pGameUser = pFactory->AllocGameUser();
		if ( pGameUser !=NULL ) {
            m_pFreeUserList.push_back(pGameUser);
		}
	}

    return TRUE;
}

int GameRoom::Update()
{
    GameTable * pTable = NULL;
    GameUser * _pUser[3] = { NULL };

    if ( m_pWaitingUserList.size() > DF_MAX_USERS )
    {
        m_pEmptyTableList.Lock();

        pTable = m_pEmptyTableList.front();
        m_pEmptyTableList.pop_front();

        m_pEmptyTableList.Unlock();

        if ( pTable != NULL )
        {
            if ( GetTableAllUser( _pUser, 3 ) == TRUE )
            {
                m_pActiveUser[_pUser[0]->GetHashKey()] = _pUser[0];
                m_pActiveUser[_pUser[1]->GetHashKey()] = _pUser[1];
                m_pActiveUser[_pUser[2]->GetHashKey()] = _pUser[2];

                pTable->JoinGame(_pUser[0]);
                pTable->JoinGame(_pUser[1]);
                pTable->JoinGame(_pUser[2]);

                m_pActiveTable[pTable->m_uiTableIndex] = pTable;

                return TRUE;
            }
        }

        m_pEmptyTableList.Lock();
        m_pEmptyTableList.push_back( pTable );
        m_pEmptyTableList.Unlock();
    }
}

GameUser * GameRoom::AllocUser()
{
    GameUser *_pUser = NULL;

    m_pFreeUserList.Lock();
    _pUser = m_pFreeUserList.front();
	m_pFreeUserList.pop_front();
    m_pFreeUserList.Unlock();

    return _pUser;
}

int GameRoom::AddWaiting( GameUser * _pUser )
{
    if ( _pUser != NULL ) {
        m_pWaitingUserList.Lock();
        m_pWaitingUserList.push_back(_pUser);
        m_pWaitingUserList.Unlock();
    }
}

GameUser * GameRoom::FindUser( WORD _userid ) {
    return m_pActiveUser[_userid];
}

int GameRoom::GetTableAllUser(GameUser ** user, WORD wSize)
{
    GameUser *pUser = NULL;

    int idx = 0;

    m_pWaitingUserList.Lock();

    while( TRUE )
    {
        pUser = m_pWaitingUserList.front();
        m_pWaitingUserList.pop_front();

        if ( pUser->m_byRemove == TRUE ) {
            m_pFreeUserList.Lock();
            m_pFreeUserList.push_back(pUser);
            m_pFreeUserList.Unlock();
        }

        if ( pUser == NULL ) {
            break;
        }

        if ( idx < wSize ) {
            user[idx] = pUser;
            ++idx;
        }
    }

    m_pWaitingUserList.Unlock();

    // 有效用户不够
    if ( idx != (wSize - 1) )
    {
        m_pWaitingUserList.Lock();
        for(int i=0; i<idx; ++i) {
            m_pWaitingUserList.push_back( user[i] );
        }
        m_pWaitingUserList.Unlock();
        return FALSE;
    }

    return TRUE;
}

int GameRoom::ReleaseTable(WORD _tableid)
{
    GameTable *pTable = m_pActiveTable[_tableid];

    if ( pTable != NULL )
    {
        pTable->ClearGame();

        m_pEmptyTableList.Lock();
        m_pEmptyTableList.push_back(pTable);
        m_pEmptyTableList.Unlock();

        return TRUE;
    }
    return FALSE;
}
