#ifndef _PROTOCOLAG_H_INCLUDED_
#define _PROTOCOLAG_H_INCLUDED_

/***** 游戏服务器 -> 代理服务器 *****/
/***** Agent -> Game *****/


enum eGAME_PROTOCOL {
	
	StartGame_REQ 		= 2000,
	StartGame_ANC,
	
	JoinRoom_REQ, 				// 加入房间请求：【玩家X】
	JoinRoom_ANC, 				// 加入房间应答：【房间ID, 玩家{1,2,3}】
	
	JoinTable_REQ, 				// 加入桌子请求
	JoinTable_ANC 		= 2005, // 加入桌子应答
	
	JoinGame_REQ, 				// 加入房加：【玩家X】
	JoinGame_ANC, 				// 加入房加：【房间ID, 玩家{1,2,3}】
	
	InitCards_BRD, 				// 服务器给所有玩家发牌：【牌数、牌串】
	
	CallLandlord_REQ, 			// 叫地主
	CallLandlord_ANC, 			// 
	
	GrabLandlord_REQ, 			// 抢地主 请求
	GrabLandlord_ANC, 			// 抢地主 应答
	GrabLandlord_BRD, 			// 抢地主 广播
	
	ShowCards_REQ, 				// 明牌
	ShowCards_ANC,

	Discards_REQ, 				// 玩家出牌：【牌数、牌值串】
	Discards_ANC, 				// 出牌应答：0-不合格、1-合格
	Discards_INVALID, 			// 无效出牌
	
	Pass_REQ, 					
	Pass_ANC,	
	
	MaxCards_BRD, 				// 单圈胜利：0-不合格、1-合格
	WinPlayer_BRD, 				// 单局胜利：0-不合格、1-合格
	
	EndGame_SYN,
};

#endif // _PROTOCOLGA_H_INCLUDED_
