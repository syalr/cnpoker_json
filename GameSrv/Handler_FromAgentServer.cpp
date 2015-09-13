#include "Handler_FromAgentServer.h"
#include "GameServer.h"
#include "GameRoom.h"
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
	MSG_JOINTABLE_REQ * recvMsg = (MSG_JOINTABLE_REQ *) pMsg;
	printf("[JoinTable_REQ] Port = %d]\n", recvMsg->m_wUserPort );

    GameUser * pUser = g_pGameRoom.FindUser(recvMsg->m_wUserPort);
    if (pUser != NULL) {
        g_pGameRoom.AddWaiting( pUser );
        return;
    }
}

// 叫地主
HANDLER_IMPL( CallBank_REQ )
{
	printf("[CallBank_REQ]\n");

	MSG_CALLBANK_REQ * recvMsg = (MSG_CALLBANK_REQ *)pMsg;
	printf("[CallBank_REQ] Port = %d\n", recvMsg->m_wUserPort );

    GameUser * pUser = g_pGameRoom.FindUser(recvMsg->m_wUserPort);
    if (pUser != NULL) {
        pUser->CallBank();
        return;
    }
}

HANDLER_IMPL( ShowCards_REQ )
{
	printf("[ShowCards_REQ]\n");

	MSG_SHOWCARDS_REQ * recvMsg = (MSG_SHOWCARDS_REQ *)pMsg;
	printf("[ShowCards_REQ] Port = %d\n", recvMsg->m_wUserPort );

	GameUser * pUser = g_pGameRoom.FindUser(recvMsg->m_wUserPort);
    if (pUser != NULL) {
        pUser->ShowCards();
        return;
    }

}


#if 0
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
#endif
