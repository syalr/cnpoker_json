#ifndef _AGENTSERVER_H_INCLUDED_
#define _AGENTSERVER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "AgentFactory.h"

using namespace std;

class AgentServer
{
	enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };
	
public:
	AgentServer(void);
	~AgentServer(void);

	BOOL Init();
	
	void StartServerSideListen();
	
	void StartClientSideListen();
	
	BOOL MaintainConnection();
	
	BOOL Update( DWORD dwDeltaTick );
	
	BOOL SendToGameServer( BYTE * pMsg, WORD wSize);
	
	ServerSession * GetGameServerSession() const;
	
	// User Session
	BOOL SendToClient( BYTE * pMsg, WORD wSize );
	BOOL SetUserSession( WORD wIndex, UserSession * pSession );
	
	//BOOL ConnectToServer(ServerSession * pSession, char * pszIP, WORD wPort);
	
private:
	BOOL 	m_bShutdown;
	
	IOCPServer * m_pIOCPServer;
	
	ServerSession * m_pGameServer;
	
	ServerSession * m_pLoginServer;
	
	// UserKey = Key;  maxsize = 0xFFFF+1;
	UserSession * m_pUserSession[PORT_MAX + 1];
};

extern AgentServer * g_AgentServer;

#endif // _AGENTSERVER_H_INCLUDED_
