#ifndef _GAMEUSER_H_INCLUDED_
#define _GAMEUSER_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include <Common.h>
#include <Public.h>


using namespace A;

class GameUser : public LinkD_T<GameUser>
{
    enum
    {
        eGU_EMPTY   = 0 ,
        eGU_OWNED       ,
    };

public:
    GameUser();

    ~GameUser();

    int JoinGame(WORD _table, BYTE _seat);

    int FigureOutDiscards(BYTE * pCards, unsigned int uiSize);

    int GetCount() const { return m_byCCount; }

    int Clear();

    int SetCards(BYTE *poker, WORD wSize);

    void SetHashKey ( WORD _userkey) { m_wUserKey = _userkey; }
    WORD GetHashKey () const { return m_wUserKey; }

    void SetUserid ( UINT _userid) { m_uiUserid = _userid; }
    WORD GetUserid () const { return m_uiUserid; }

protected:
    friend class GameRoom;
    friend class GameTable;

    UINT m_uiUserid;     // 用户ID
    WORD m_wUserKey;     // 用记Key

    WORD m_wTable;       // 桌位号
    BYTE m_bySeat;       // 坐位号

    BYTE m_byCCount;    // 卡牌数量
	BYTE m_szCards[CNPOKER_CARD_LEN_1];     // 自己手上的牌 private to public
};

#endif
