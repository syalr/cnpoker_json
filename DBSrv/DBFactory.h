#ifndef _AGENT_FACTORY_H_INCLUDED_
#define _AGENT_FACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>

#include "ServerSession.h"
#include "TempServerSession.h"
#include "GameServerSession.h"

using namespace A;

class DBFactory : public Singleton<DBFactory>
{

public:
	DBFactory();
	~DBFactory();

private:
	MemoryFactory<TempServerSession>	* m_pTempServerSessionPool;
	MemoryFactory<GameServerSession>	* m_pGameServerSessionPool;

public:
	void Init(void);
	void Release(void);

	// Server
	TempServerSession * AllocTempServerSession();
	void FreeTempServerSession(TempServerSession * pServerSession);

	GameServerSession * AllocGameServerSession();
	void FreeGameServerSession(GameServerSession * pServerSession);
};

#endif
