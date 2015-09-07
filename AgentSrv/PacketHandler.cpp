#include "PacketHandler.h"
#include "AgentServer.h"

//#include "Handler_FromClient.h"

#include "Handler_FromGameServer.h"
#include "Handler_FromLoginServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	//m_pFuncMap_CA = new FunctionMap;
	m_pFuncMap_AG = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	//SAFE_DELETE(m_pFuncMap_CA);
	SAFE_DELETE(m_pFuncMap_AG);
}

BOOL PacketHandler::RegisterHandler()
{
	//Register_CA();
	Register_AG();
	return TRUE;
}	

//void PacketHandler::Register_CA()
//{	
//	AddHandler_CA( Login_Protocol, Login_REQ, Handler_FromClient::OnLogin_REQ );
//	
//	AddHandler_CA( Login_Protocol, ReLogin_REQ, Handler_FromClient::OnReLogin_REQ );	
//	AddHandler_CA( Login_Protocol, Logout_REQ, Handler_FromClient::OnLogout_REQ );
//
//	// sylar 2015-08-16
//	AddHandler_CA( Games_Protocol, StartGame_REQ, Handler_FromClient::OnStartGame_REQ );	
//	AddHandler_CA( Games_Protocol, JoinRoom_REQ, Handler_FromClient::OnJoinRoom_REQ );
//	AddHandler_CA( Games_Protocol, JoinTable_REQ, Handler_FromClient::OnJoinTable_REQ );
//	AddHandler_CA( Games_Protocol, ShowCards_REQ, Handler_FromClient::OnShowCards_REQ );
//	AddHandler_CA( Games_Protocol, Discards_REQ, Handler_FromClient::OnDiscards_REQ );
//	AddHandler_CA( Games_Protocol, EndGame_SYN, Handler_FromClient::OnEndGame_SYN );	
//	AddHandler_CA( Games_Protocol, InitCards_BRD, Handler_FromClient::OnInitCards_BRD );
//}

void PacketHandler::Register_AG()
{
	AddHandler_AG( Login_Protocol, Login_ANC, Handler_FromGameServer::OnLogin_ANC );
	//AddHandler_AG( AG_Connect, AG_Logout_ANC, Handler_FromGameServer::OnAG_Logout_ANC );
	
	
	//AddHandler_AG( AG_Connect, AG_StartGame_ANC, Handler_FromGameServer::OnAG_StartGame_ANC);
	
#if 0
	AddHandler_AG(AG_Connect_Protocol, AG_Heratbeat_ANC, Handler_FromGameServer::OnAG_Heratbeat_ANC);
	
	
	AddHandler_AG(AG_Client_Protocol, AG_Relogin_ANC, Handler_FromGameServer::OnAG_Relogin_ANC);
	
	
	AddHandler_AG( Games_Protocol, StartGame_ANC, Handler_FromGameServer::OnAG_StartGame_ANC);
	AddHandler_AG( Games_Protocol, JoinRoom_ANC, Handler_FromGameServer::OnAG_JoinRoom_ANC);
	AddHandler_AG( Games_Protocol, JoinTable_ANC, Handler_FromGameServer::OnAG_JoinTable_ANC);
	AddHandler_AG( Games_Protocol, ContendWithBanker_ANC, Handler_FromGameServer::OnAG_ContendWithBanker_ANC);
	AddHandler_AG( Games_Protocol, ShowCards_ANC, Handler_FromGameServer::OnAG_ShowCards_ANC);
	AddHandler_AG( Games_Protocol, Discards_ANC, Handler_FromGameServer::OnAG_Discards_ANC);
	AddHandler_AG( Games_Protocol, EndGame_ANC, Handler_FromGameServer::OnAG_EndGame_ANC);
#endif
}

//BOOL PacketHandler::AddHandler_CA( WORD category, WORD protocol, fnHandler_c fnHandler)
//{
//	FUNC_CA * pFuncInfo	= new FUNC_CA;
//	//printf("category:%d,protocol:%d\n", category, protocol);	
//	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
//	//printf("m_dwFunctionKey:%d\n", pFuncInfo->m_dwFunctionKey);
//	pFuncInfo->m_fnHandler		= fnHandler;
//	
//	return m_pFuncMap_CA->Add( pFuncInfo );
//}

BOOL PacketHandler::AddHandler_AG( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_AG * pFuncInfo	= new FUNC_AG;
	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_AG->Add( pFuncInfo );
}

//VOID PacketHandler::ParsePacket_CA( UserSession * pSession, MSG_BASE * pMsg, WORD wSize )
//{
//	assert(NULL != pMsg);	
//	
//	printf("PacketHandler::ParsePacket CA \n");
//	
//	FUNC_CA * pFuncInfo = (FUNC_CA *)m_pFuncMap_CA->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
//	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );
//
//	//AddLogMsg(LOG_OUT, "ParsePacket_CA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
//}

VOID PacketHandler::ParsePacket_AG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	printf("PacketHandler::ParsePacket AG \n");
	
	FUNC_AG * pFuncInfo = (FUNC_AG *)m_pFuncMap_AG->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_AG Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}
