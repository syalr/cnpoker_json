#include "PacketHandler.h"
#include "DBServer.h"
#include "Handler_FromGameServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_GD = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_GD);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_GD();
	return TRUE;
}

void PacketHandler::Register_GD()
{
	AddHandler_GD(Login_Protocol, Login_REQ, Handler_FromGameServer::OnLogin_REQ);

#if 0
	AddHandler_GD(Games_Protocol, GD_Logout_REQ, Handler_FromGameServer::OnGD_Logout_REQ);
	AddHandler_GD(Games_Protocol, GD_Save_CMD, Handler_FromGameServer::OnGD_Save_CMD);
	AddHandler_GD(Games_Protocol, GD_Update_CMD, Handler_FromGameServer::OnGD_Update_CMD);
#endif
}

BOOL PacketHandler::AddHandler_GD( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_GD * pFuncInfo	= new FUNC_GD;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return m_pFuncMap_GD->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_GD( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);

	printf("PacketHandler::ParsePacket GD \n");
	FUNC_GD * pFuncInfo = (FUNC_GD *)m_pFuncMap_GD->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );
}

