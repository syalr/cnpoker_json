#ifndef _AUTO_TEST_H_INCLUDED_
#define _AUTO_TEST_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

#include "ServerSession.h"

using namespace std;

class AutoTest
{
	enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };
	
public:
	AutoTest(void);
	~AutoTest(void);

	BOOL Init();
	BOOL ConnectToServer(ServerSession * pSession);
	
	BOOL MaintainConnection();
	BOOL Update( DWORD dwDeltaTick );
	
	//BOOL SendToDBServer( BYTE * pMsg, WORD wSize);
	//ServerSession * GetDBServerSession() const;
	
private:
	BOOL 	m_bShutdown;
	IOCPServer * m_pIOCPServer;
	
	// ���ݿ�
	ServerSession * m_pDBServer;
	
	// ��Ϸ������
	ServerSession * m_pGameServer;

};

extern AutoTest * g_AutoTest;

#endif // _AUTO_TEST_H_INCLUDED_

