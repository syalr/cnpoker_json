#ifndef _PROTOCOLAG_H_INCLUDED_
#define _PROTOCOLAG_H_INCLUDED_

/***** 游戏服务器 -> 代理服务器 *****/
/***** Agent -> Game *****/


enum eGAME_PROTOCOL {

	StartGame_REQ 		= 2000,
	StartGame_ANC,

	// JoinRoom_REQ, 			// 加入房间请求：【玩家X】
	// JoinRoom_BRD, 			// 加入房间应答：【房间ID, 玩家{1,2,3}】

	JoinTable_REQ, 			    // 加入桌子请求
	JoinTable_BRD, 			    // 加入桌子应答

	InitCards_BRD, 				// 服务器给所有玩家发牌：【牌数、牌串】

	CallBank_REQ, 			    // 叫庄
	CallBank_BRD, 			    //

	ShowCards_REQ, 				// 明牌
	ShowCards_BRD,

	Discards_REQ, 				// 玩家出牌：【牌数、牌值串】
	Discards_BRD, 				// 出牌应答：0-不合格、1-合格

	Pass_REQ,
	Pass_BRD,

	MaxCards_BRD, 				// 单圈胜利：0-不合格、1-合格
	WinPlayer_BRD, 				// 单局胜利：0-不合格、1-合格
	End_BRD,
};

#endif // _PROTOCOLGA_H_INCLUDED_
