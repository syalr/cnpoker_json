#include "AgentFactory.h"

AgentFactory::AgentFactory()
{
	m_pUserSessionPool	 = NULL;	
	
	m_pTempServerSessionPool = NULL;
	m_pGameServerSessionPool = NULL;
	
	// Rootid
	m_pRootIDPool = NULL;
}

AgentFactory::~AgentFactory()
{
	if (m_pUserSessionPool) 		delete m_pUserSessionPool;	
	
	if (m_pTempServerSessionPool) 	delete m_pTempServerSessionPool;
	if (m_pGameServerSessionPool) 	delete m_pGameServerSessionPool;
	
	// Rootid
	if (m_pRootIDPool) 				delete m_pRootIDPool;
}

void AgentFactory::Init()
{
	m_pUserSessionPool 			= new MemoryFactory<UserSession>;
	
	m_pTempServerSessionPool 	= new MemoryFactory<TempServerSession>;
	m_pGameServerSessionPool 	= new MemoryFactory<GameServerSession>; 
	
	m_pRootIDPool 				= new MemoryFactory<RootID>; 
	
	// UserSession
	m_pUserSessionPool->Initialize(999,1); // 多少才合适?
	// Server
	m_pTempServerSessionPool->Initialize(5,1); // 多少才合适?
	m_pGameServerSessionPool->Initialize(1,1);
	
	// RootID
	m_pRootIDPool->Initialize(999,1); // 多少才合适?
}

// UserSession
UserSession * AgentFactory::AllocUserSession() {
	if (m_pUserSessionPool == NULL) {
		return NULL;
	}
	return m_pUserSessionPool->Alloc();
}

void AgentFactory::FreeUserSession(UserSession * pUser) {
	return m_pUserSessionPool->Free(pUser);
}

// Server
TempServerSession * AgentFactory::AllocTempServerSession() {
	if (m_pTempServerSessionPool == NULL) {
		return NULL;
	}
	TempServerSession * pSession = m_pTempServerSessionPool->Alloc();
	if ( pSession != NULL ) {
		pSession->Clear();
	}
		
	return pSession;
}

void AgentFactory::FreeTempServerSession(TempServerSession * pServerSession) {
	return m_pTempServerSessionPool->Free(pServerSession);
}

GameServerSession * AgentFactory::AllocGameServerSession() {
	if (m_pGameServerSessionPool == NULL) {
		return NULL;
	}
	GameServerSession * pSession = m_pGameServerSessionPool->Alloc();
	if ( pSession != NULL ) {
		pSession->Clear();
	}
		
	return pSession;	
}

void AgentFactory::FreeGameServerSession(GameServerSession * pServerSession) {
	return m_pGameServerSessionPool->Free(pServerSession);
}

// Rootid
RootID * AgentFactory::AllocRootID()
{
	if (m_pRootIDPool == NULL) {
		return NULL;
	}
	RootID * pRoot = NULL;
	pRoot = m_pRootIDPool->Alloc();
	if ( pRoot != NULL ) {
		pRoot->Clear();
	}
		
	return pRoot;	
}

void AgentFactory::FreeRootID(RootID * pRoot)
{
	return m_pRootIDPool->Free(pRoot);
}

