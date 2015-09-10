#ifndef _GAMETABLE_H_INCLUDED_
#define _GAMETABLE_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include <Common.h>
#include <Public.h>
#include "GameUser.h"

using namespace A;

class GameTable : public LinkD_T<GameTable>
{
    enum eCHAIR
    {
        eGT_EMPTY       = 0,     // 坐位为空
        eGT_WAITING        ,      // 坐下

        eGT_STARTGAME      ,     // 开始游戏
        eGT_GETBANK        ,     // 抢庄
        eGT_GIVEUP         ,     // 放弃抢庄

        eGT_DISCOUNT       ,
        eGT_PASS           ,

        eGT_CHAIR1         ,
        eGT_CHAIR2         ,
        eGT_CHAIR3         ,
    };

public:

	GameTable();
	~GameTable();

	int JoinGame( GameUser * pUser );
    int QuitGame( GameUser * pUser );
    int IsEmpty();

	int StartGame();    // 判断是否需要洗牌
    int Shuffle();  // 洗牌
    int Alloc();    // 分牌
    int GetBank( BYTE _bySeat, BYTE _getBank = TRUE);  // 抢庄

    int Discards(BYTE * pCards, unsigned int uiSize, BYTE _bySeat);  // 出牌
    int Pass(BYTE _bySeat);     // 不出

    int IsWoned();              // 当前坐位的人是否赢了这局
    int IsEndGame();            // 游戏是否束
    int NextUser();             // 下一个出牌用户

    int Settlement();           // 结算
    int ClearTable();           // 清理桌面
    int ClearGame();            // 清理游戏


protected:

	int Broadcast(BYTE *pMsg, WORD wSize); // 发送消息给其他游戏玩家

protected:
    friend class GameUser;
    friend class GameRoom;

    UINT m_uiTableIndex;

	BYTE m_byAllCards[CNPOKER_CARD_LEN_1];
    BYTE m_byDiscards[CNPOKER_CARD_LEN_1];

    static UINT m_maxCallBanks; // 叫地主次数
    UINT m_calledBanks;         // 已叫地主次数

	UINT m_dwLandlord;          // 地主
	BYTE m_byWoned;             // 地主赢为 0; 地主输为 1;
	BYTE m_byExtraCards[3];     // 地主主额外的三张牌

	BYTE m_byDiscardCurr;       // 现在出牌的坐位
	BYTE m_byDiscardLast;       // 最后出牌的坐位
    BYTE m_bySatus[3];          // 0, 1
	GameUser * m_pGameUser[3];  // 参加的游戏用户

    ePK_TYPE m_ePkType;     // 打出牌的类型
	BYTE m_byCmpValue;      // 比较的值
	BYTE m_byCmpCount;      // 比较的值 的 个数
};


#endif
