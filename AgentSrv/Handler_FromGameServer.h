#ifndef _HANDLER_FROMGAMESERVER_H_INCLUDED_
#define _HANDLER_FROMGAMESERVER_H_INCLUDED_

#include <Common.h>

#include "ServerSession.h"

#define HANDLER_DECL( p )			static VOID On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
#define HANDLER_IMPL( p )			VOID Handler_FromGameServer::On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )

class Handler_FromGameServer
{
public:
	Handler_FromGameServer(void);
	~Handler_FromGameServer(void);

	HANDLER_DECL( Login_ANC);
	
#if 0		
	HANDLER_DECL( Logout_ANC);
	
	HANDLER_DECL( StartGame_ANC );

	HANDLER_DECL( Heartbeat_SYN );
	
	HANDLER_DECL( Relogin_SYN );
	//
	HANDLER_DECL( StartGame_REQ );
	HANDLER_DECL( JoinRoom_REQ );
	HANDLER_DECL( JoinTable_REQ );
	HANDLER_DECL( ShowCards_REQ );
	HANDLER_DECL( Discards_REQ );
	HANDLER_DECL( EndGame_REQ );
#endif
};


#endif
