#include "DBFactory.h"

DBFactory::DBFactory()
{
	m_pTempServerSessionPool = NULL;
	m_pGameServerSessionPool = NULL;
}

DBFactory::~DBFactory()
{
	if (m_pTempServerSessionPool) 	delete m_pTempServerSessionPool;
	if (m_pGameServerSessionPool) 	delete m_pGameServerSessionPool;
}

void DBFactory::Init()
{
    m_pTempServerSessionPool 	= new MemoryFactory<TempServerSession>;
	m_pGameServerSessionPool 	= new MemoryFactory<GameServerSession>;

	m_pTempServerSessionPool->Initialize(10,1);
	m_pGameServerSessionPool->Initialize(9,1);
}

TempServerSession * DBFactory::AllocTempServerSession() {
	if (m_pTempServerSessionPool == NULL) {
		return NULL;
	}
	TempServerSession * pSession = m_pTempServerSessionPool->Alloc();
	if ( pSession != NULL ) {
		pSession->Clear();
	}
	return pSession;
}
void DBFactory::FreeTempServerSession(TempServerSession * pServerSession) {
	return m_pTempServerSessionPool->Free(pServerSession);
}

GameServerSession * DBFactory::AllocGameServerSession() {
	if (m_pGameServerSessionPool == NULL) {
		return NULL;
	}
	return m_pGameServerSessionPool->Alloc();
}
void DBFactory::FreeGameServerSession(GameServerSession * pServerSession) {
	return m_pGameServerSessionPool->Free(pServerSession);
}
