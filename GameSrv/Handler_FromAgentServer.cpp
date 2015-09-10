#include "Handler_FromAgentServer.h"
#include "GameServer.h"
#include "Json_Login.h"
#include "Json_Discard.h"

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

	Json_Login_REQ js_login;
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
}

HANDLER_IMPL( Logout_REQ )
{
	printf("Logout_REQ\n");
}


HANDLER_IMPL( JoinRoom_REQ )
{
	printf("[JoinRoom_REQ]\n");
}

HANDLER_IMPL( JoinTable_REQ )
{
	MSG_JOINTABLE_REQ * recv = (MSG_JOINTABLE_REQ *) pMsg;
	printf("[JoinTable_REQ userport = %d]\n", recv->m_wUserPort );


}

#if 0

HANDLER_IMPL( StartGame_REQ )
{
	printf("StartGame_REQ\n");

	MSG_BASE_FORWARD * pRecvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", pRecvMsg->m_wUserPort );


    // if ()
    {

    }

}

// 叫地主
HANDLER_IMPL( CallLandlord_REQ )
{
	printf("CallLandlord_REQ\n");

	MSG_BASE_FORWARD * pRecvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", pRecvMsg->m_wUserPort );



}

HANDLER_IMPL( ShowCards_REQ )
{
	printf("ShowCards_REQ\n");

	MSG_SHOWCARDS_REQ * pRecvMsg = (MSG_SHOWCARDS_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwUserID;

	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}

	pUser->ShowCards();
}

HANDLER_IMPL( Discards_REQ )
{
	printf("Discards_REQ\n");

	MSG_DISCARDS_REQ * pRecvMsg = (MSG_DISCARDS_REQ *) pMsg;
	DWORD dwUserID = pRecvMsg->m_dwUserID;

	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}

	pUser->Discards(pRecvMsg->byDiscards, pRecvMsg->uiSize);

	// 手上牌已打完，取得胜利
	if ( pUser->IsWinTheGame() ) {
            /*
		MSG_WINPLAYER_BRD msg2;
		msg2.m_dwUserID = dwUserID;

		g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) ); */
	}

}

HANDLER_IMPL( Pass_REQ )
{
	printf("Pass_REQ\n");

	MSG_PASS_REQ * pRecvMsg = ( MSG_PASS_REQ *) pMsg;
	DWORD dwUserID = pRecvMsg->m_dwUserID;

	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}

	pUser->Pass(); // 要不起

	MSG_PASS_BRD msg2;
	msg2.m_dwUserID = dwUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
}

#endif
