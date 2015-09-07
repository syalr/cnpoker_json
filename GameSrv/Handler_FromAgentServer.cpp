#include "Handler_FromAgentServer.h"

#include "GameServer.h"
#include "GameUserManager.h"

#include "Json_LoginREQ.h"


Handler_FromAgentServer::Handler_FromAgentServer() 
{
	
}

Handler_FromAgentServer::~Handler_FromAgentServer() 
{
	
}

HANDLER_IMPL( Login_REQ )
{
	printf("Login_REQ\n");
	
	
	MSG_BASE_FORWARD * pRecvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", pRecvMsg->m_wUserPort );
	
	char json_msgs[1024] = {0};
	memcpy( json_msgs, ( ( BYTE * )pMsg) + sizeof( pRecvMsg ), wSize - sizeof( pRecvMsg ) );
	
	Json_LoginREQ js_login;
	int nRet = js_login.ParseJson( (char * ) json_msgs );
	if ( nRet != 0 ) {
		// Login_NAK返回给 Agent
		return;
	}
	
	MSG_LOGIN_REQ sendDB;
	if ( js_login.GetMsg( &sendDB ) != NULL ) {
		sendDB.m_wUserPort = pRecvMsg->m_wUserPort;
		g_GameServer->SendToDBServer( (BYTE*)&sendDB, sizeof( sendDB ) );
	}
	
#if 0	
	MSG_AG_LOGIN_REQ * pRecvMsg = (MSG_AG_LOGIN_REQ *)pMsg;
	
	DWORD uiRootID = pRecvMsg->m_uiRootID;
	printf("uiRootID = %d\n", uiRootID);
	
	MSG_GD_LOGIN_REQ msg2;
	msg2.m_dwParameter = pRecvMsg->m_dwParameter; // User ID
	msg2.m_uiRootID = uiRootID;
	
	g_GameServer->SendToDBServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

HANDLER_IMPL( Logout_REQ )
{
	printf("Logout_REQ\n");
#if 0
	MSG_AG_LOGOUT_REQ * pRecvMsg = (MSG_AG_LOGOUT_REQ *)pMsg;
	
	DWORD uiRootID = pRecvMsg->m_uiRootID;
	printf("uiRootID = %d\n", uiRootID);
	
	MSG_GD_LOGOUT_REQ msg2;
	msg2.m_dwParameter = pRecvMsg->m_dwParameter; // User ID
	msg2.m_uiRootID = uiRootID;
	g_GameServer->SendToDBServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

HANDLER_IMPL( StartGame_REQ )
{
	printf("StartGame_REQ\n");
#if 0
	MSG_AG_START_GAME_REQ * pRecvMsg = (MSG_AG_START_GAME_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	// 先查找用户
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	//pUser->StartGame(); // Do nothing
	
	// 返回应答数据给Agent
	MSG_AG_START_GAME_ANC msg2;
	msg2.m_dwParameter = dwUserID;
	
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

HANDLER_IMPL( JoinRoom_REQ )
{
	printf("JoinRoom_REQ\n");
#if 0	
	MSG_AG_JOINROOM_REQ * pRecvMsg = (MSG_AG_JOINROOM_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	unsigned int uiRoomNumber = pRecvMsg->m_uiRoomNumber;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->SetRoomNumber(uiRoomNumber);

	// 回复 AG_JoinRoom_ANC 信息
	MSG_AG_JOINROOM_ANC msg2;
	msg2.m_dwParameter = dwUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

HANDLER_IMPL( JoinTable_REQ )
{
	printf("JoinTable_REQ\n");
#if 0	
	MSG_AG_JOINTABLE_REQ * pRecvMsg = (MSG_AG_JOINTABLE_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	unsigned int uiTableNumber = pRecvMsg->m_uiTableNumber;
	//unsigned int uiSeat = pRecvMsg->m_uiSeat;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->SetTableNumber(uiTableNumber);
	
	for(int i=0; i<3; ++i)
	{
		if( pUser->m_TableInfo[uiTableNumber].m_uiUserKey[i] == 0 ) {
			pUser->m_TableInfo[uiTableNumber].m_uiUserKey[i] = dwUserID;
			pUser->SetSeat(i); // 设置座位
			break;
		}
	}
	
	// 回复 AG_JoinTable_ANC 信息
	//MSG_AG_JOINTABLE_ANC msg2;
	//g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

HANDLER_IMPL( InitCards_BRD )
{
	printf("InitCards_BRD\n");

#if 0	
	MSG_AG_INITCARDS_BRD * pRecvMsg = (MSG_AG_INITCARDS_BRD *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->InitCards(); // 初始化牌
	pUser->AllocCards(); // 发给每个玩家的牌

	
	// 返回 消息包 给 Agent
	MSG_AG_INITCARDS_ANC msg2;
	msg2.m_byParameter = dwUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

// 叫地主
HANDLER_IMPL( CallLandlord_REQ )
{
	printf("CallLandlord_REQ\n");
#if 0	
	MSG_AG_CALLLANDLOARD_REQ * pRecvMsg = (MSG_AG_CALLLANDLOARD_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->CallLandlord(pRecvMsg->m_byCall);
	
	// 返回 消息包 给 Agent
	MSG_AG_CALLLANDLOARD_ANC msg2;
	msg2.m_byParameter = dwUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

// 抢地主
HANDLER_IMPL( GrabLandlord_REQ )
{
	printf("GrabLandlord_REQ\n");
#if 0	
	MSG_AG_GRABLANDLOARD_REQ * pRecvMsg = (MSG_AG_GRABLANDLOARD_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->GrabLandlord(); // 抢地主，抢地主次数加1.最终由Agent算出谁是地主
	
	// 返回 消息包 给 Agent
	MSG_AG_GRABLANDLOARD_ANC msg2;
	msg2.m_byParameter = dwUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

HANDLER_IMPL( GrabLandlord_BRD )
{
	printf("GrabLandlord_BRD\n");
#if 0	
	MSG_AG_GRABLANDLOARD_BRD * pRecvMsg = (MSG_AG_GRABLANDLOARD_BRD *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->GetExtraCards(); // 获取桌面的3张牌
#endif	
}

HANDLER_IMPL( ShowCards_REQ )
{
	printf("ShowCards_REQ\n");
#if 0	
	MSG_AG_SHOWCARDS_REQ * pRecvMsg = (MSG_AG_SHOWCARDS_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->ShowCards();
#endif	
}

HANDLER_IMPL( Discards_REQ )
{
	printf("Discards_REQ\n");
#if 0
	MSG_AG_DISCARDS_REQ * pRecvMsg = (MSG_AG_DISCARDS_REQ *) pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->Discards(pRecvMsg->m_byDiscards, pRecvMsg->m_uiSize);
	
	// 手上牌已打完，取得胜利
	if ( pUser->IsWinTheGame() ) {
		MSG_AG_WINPLAYER_BRD msg2;
		msg2.m_dwParameter = dwUserID;
		
		g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
	}
#endif	
}

HANDLER_IMPL( Pass_REQ )
{
	printf("Pass_REQ\n");
#if 0	
	MSG_AG_PASS_REQ * pRecvMsg = (MSG_AG_PASS_REQ *)pMsg;	
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->Pass(); // 要不起
	
	MSG_AG_PASS_ANC msg2;
	msg2.m_dwParameter = dwUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

HANDLER_IMPL( EndGame_SYN )
{
	printf("EndGame_SYN\n");
}

