#ifndef _GameRoom_H_INCLUDED_
#define _GameRoom_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include <Common.h>
#include <Public.h>
#include "GameTableList.h"
#include "GameUserList.h"

#define DF_TABLE_PS      3
#define DF_MAX_TABLES 0xFF
#define DF_MAX_USERS  0xFF

class GameRoom
{
public:

    enum
    {
        eGR_OK              = 0,         // ok
        eGR_ROOMFULL           ,         // 房间满了
        eGR_FOUNDTABLE         ,         // 找不到桌子
    };

public:
    GameRoom();

    virtual ~GameRoom();

    int Create(WORD wTables, WORD wUsers);

    int Update();

    GameUser * AllocUser();

    int AddWaiting(GameUser *); // 活动用户

    int ReleaseTable(WORD _tableid);



protected:

    // Table
    GameTable * m_pActiveTable[DF_MAX_TABLES];
    GameTableList m_pEmptyTableList;

    // User
    GameUser * m_pActiveUser[DF_MAX_USERS];
    GameUserList m_pFreeUserList;
    GameUserList m_pWaitingUserList;
};

#endif
