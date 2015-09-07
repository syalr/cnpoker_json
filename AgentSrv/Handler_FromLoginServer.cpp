#include "Handler_FromLoginServer.h"
#include "AgentServer.h"
#include "User.h"
#include "UserManager.h"

#include "RootidManager.h"

Handler_FromLoginServer::Handler_FromLoginServer() 
{
	
}

Handler_FromLoginServer::~Handler_FromLoginServer() 
{
	
}

HANDLER_IMPL( Login_ANC )
{
	printf(">>> Login_ANC\n");
#if 0	
	MSG_AL_LOGIN_ANC * pRecvMsg = (MSG_AL_LOGIN_ANC *) pMsg;
	
	User * pUser = g_UserManager.FindUser(pRecvMsg->m_dwParameter);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecvMsg->m_dwParameter);
		return;
	}
	
	// 连接到Game
	MSG_AG_LOGIN_REQ msg2;
	msg2.m_uiRootID = pRecvMsg->m_uiRootID;
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
#endif	
}

#if 0
HANDLER_IMPL( SaveUserKey_SYN )
{
	printf("AL_SaveUserKey_SYN\n");
	MSG_AL_SAVEUSERKEY_SYN * pRecvMsg = (MSG_AL_SAVEUSERKEY_SYN *)pMsg;
	printf("RootID = %d, User Key = %s\n", pRecvMsg->m_uiRootID, pRecvMsg->m_byUserKey);
	
	RootID * pRoot = AgentFactory::Instance()->AllocRootID();
	if ( pRoot == NULL ) {
		printf("\nAgentFactory::Instance()->AllocRootID() Fail.\n");
		return;
	}
	pRoot->SetRootID(pRecvMsg->m_uiRootID);
	pRoot->SetUserKey(pRecvMsg->m_byUserKey);
	
	
	BOOL bRet = RootidManager::Instance()->AddRootID(pRoot);
	if ( !bRet ) {
		printf("\n[RootidManager::Instance()->AddRootID] Fail.\n");
		return;
	}
	printf("[RootidManager::Instance()->AddRootID] Success.\n");
}
#endif
