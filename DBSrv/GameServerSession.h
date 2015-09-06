#ifndef _GAMESERVERSESSION_H_INCLUDED_
#define _GAMESERVERSESSION_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

#include "DBUser.h"
#include "ServerSession.h"

class GameServerSession : public ServerSession
{
public:
	GameServerSession();
	virtual ~GameServerSession();
	
	eSERVER_TYPE    GetServerType() { return GAME_SERVER; }
	
	virtual void    Init();
	
protected:

	virtual void	OnDisconnect();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnLogString( char * pszLog);
	

public:
	void AddUser(DBUser * pNewUser);
	DBUser * FindUser(DWORD dwKey);
	void RemoveUser(DWORD dwKey);

private:
	A::SolarHashTable<DBUser*> * m_hashDBUser;
};

#endif // _GAMESERVERSESSION_H_INCLUDED_
