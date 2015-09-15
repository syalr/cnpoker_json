#include "PacketHandler.h"
#include "AgentServer.h"

#include "Handler_FromGameServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_AG = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_AG);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_AG();
	return TRUE;
}

void PacketHandler::Register_AG()
{
	AddHandler_AG( Login_Protocol, Login_ANC, Handler_FromGameServer::OnLogin_ANC );

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

BOOL PacketHandler::AddHandler_AG( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_AG * pFuncInfo	= new FUNC_AG;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return m_pFuncMap_AG->Add( pFuncInfo );
}


VOID PacketHandler::ParsePacket_AG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	printf("PacketHandler::ParsePacket AG \n");
	FUNC_AG * pFuncInfo = (FUNC_AG *)m_pFuncMap_AG->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );
}
