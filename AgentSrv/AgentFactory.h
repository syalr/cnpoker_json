#ifndef _AGENT_FACTORY_H_INCLUDED_
#define _AGENT_FACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>

#include "ServerSession.h"
#include "TempServerSession.h"
#include "GameServerSession.h"

#include "UserSession.h"


#include "RootID.h"

using namespace A;

class AgentFactory : public Singleton<AgentFactory>
{
	
public:
	AgentFactory();
	~AgentFactory();

private:	

	MemoryFactory<UserSession> 			* m_pUserSessionPool; 

	MemoryFactory<TempServerSession>	* m_pTempServerSessionPool; 
	MemoryFactory<GameServerSession>	* m_pGameServerSessionPool; 

	// Rootid
	MemoryFactory<RootID> 				* m_pRootIDPool;
	
public:
	void Init(void);
	void Release(void);

	// UserSession
	UserSession * AllocUserSession();
	void FreeUserSession(UserSession * pUser);

	// Server
	TempServerSession * AllocTempServerSession();
	void FreeTempServerSession(TempServerSession * pServerSession);
	
	GameServerSession * AllocGameServerSession();
	void FreeGameServerSession(GameServerSession * pServerSession);
		
	// RootID
	RootID * AllocRootID();
	void FreeRootID(RootID * pRoot);
};

#endif
