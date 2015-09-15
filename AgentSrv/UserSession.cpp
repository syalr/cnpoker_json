#include "UserSession.h"
#include "AgentServer.h"
#include "AgentFactory.h"

#include <Public.h>

DWORD UserSession::m_dwClientDelay = 0xFFFFFFFF;
DWORD UserSession::m_dwServerDelay = 0xFFFFFFFF;

UserSession::UserSession()
: m_bFirst(TRUE)
{
	m_eUserType = UT_TEMP_USER;
}

UserSession::~UserSession()
{
}

BOOL UserSession::SendPacket(BYTE *pMsg, WORD wSize)
{
	return Send( (BYTE *)pMsg, wSize );
}

WORD UserSession::GetUserKey() const
{
	return m_wUserKey;
}

void  UserSession::SetUserKey(WORD dwKey)
{
	m_wUserKey = dwKey;
}

/************ protected *************/
void UserSession::Init()
{
	m_wUserKey 		= 0;
	m_bFirst 		= TRUE;

	DWORD dwCurrent = Session::GetTickCount();
	m_dwOvertime    = dwCurrent + UserSession::m_dwClientDelay;
	printf( "[UserSession::Init %d] \n", m_dwOvertime);

	this->NotPackageHeader();
}

BOOL UserSession::Update( DWORD dwDeltaTick )
{
	printf( "[UserSession::Update %d = %d] \n", dwDeltaTick, m_dwOvertime);

	// Count Down;
	if ( dwDeltaTick > m_dwOvertime ) {
		Disconnect(TRUE);
		return TRUE;
	}

	return FALSE;
}

void UserSession::CloseSession()
{
	printf(" [ UserSession::CloseSession ] \n");

	if ( m_pSession != NULL) {
		m_pSession->CloseSocket();
	}

	m_bFirst = TRUE;

}

void UserSession::Release()
{
	printf(" [ UserSession::Release ] \n");

	m_bFirst = TRUE;

	g_AgentServer->SetUserSession( this->m_wUserKey, NULL);

	AgentFactory::Instance()->FreeUserSession(this);
}

void UserSession::OnAccept( DWORD dwNetworkIndex )
{
	WORD PortKey = this->GetPort();
	if ( PortKey != 0 )
	{
		this->SetUserKey(PortKey);
		g_AgentServer->SetUserSession(PortKey, this);
		AgentFactory::Instance()->FreeUserSession( this );
		return;
	}

	char buff[1024]  =  {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{\"type\":\"text/json\"}}";

	MSG_ENTERSERVER_ANC msg2;
	sprintf( buff, format, msg2.m_dwProtocol);

	printf("[UserSession::OnAccept %s] \n", buff);
	int len = strlen(buff);
	this->Send( (BYTE*) buff,  len );
}

void UserSession::OnDisconnect()
{
	printf("[UserSession::OnDisconnect]\n");
	NetworkObject::OnDisconnect();
}

void UserSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf(">>>> [UserSession::OnRecv]\n");

	// Connected warning.
	if ( m_bFirst == FALSE ) {
		this->Release();
		return;
	}

	m_bFirst = FALSE;

	BYTE msgPlus[1024] = {0};

	// Alloc Port
	if ( m_wUserKey != 0 )
	{
		char json_msgs[1024] = {0};
		MSG_BASE_FORWARD bMsg;
		memcpy(json_msgs, pMsg + sizeof(bMsg), wSize - sizeof(bMsg)); // 跳过 头

		JsonParser js_pid;
		// 检查是否符合 json 格式
		if ( js_pid.ParseJson(json_msgs) == -1) {
			printf("Error: [UserSession::OnRecv] Parse Json fail.\n");
			return;   // Error do not a json format;
		}

		// 获取 消息id
		DWORD pid = js_pid.GetProtocol();
		printf("[UserSession::OnRecv pid = %d] \n ", pid);
		if (pid == 0) {
			printf("Error: [UserSession::OnRecv] Parse Protocol fail.\n");
			return;
		}

		MSG_BASE_FORWARD xMsg;
		xMsg.m_wUserPort = m_wUserKey; // User Key
		xMsg.m_dwMsgNumber = pid; // Message id
		memcpy( msgPlus, &xMsg, sizeof(xMsg) );
		memcpy( msgPlus + sizeof(xMsg), pMsg, wSize );
		g_AgentServer->SendToGameServer( msgPlus, wSize + sizeof(xMsg) );
	}

	//m_dwOvertime = Session::GetTickCount() + UserSession::m_dwServerDelay;
	//printf( "[UserSession::OnRecv %d = %d] \n", m_dwOvertime);
}

void UserSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{

}

void UserSession::OnLogString( char * pszLog)
{

}
