#ifndef _PUBLIC_H_INCLUDED_
#define _PUBLIC_H_INCLUDED_

struct SERVER_INFO
{
	char 	m_strIp[IP_MAX_LEN]; 	// IP
	DWORD 	m_dwPort; 				// PORT
	
	SERVER_INFO()
	{
		memset(this, 0, sizeof(SERVER_INFO));
		strcpy(m_strIp, "");
		m_dwPort = 0;		
	}	
};

#include <ctime>
#include <cstdlib>

#include <Utility.h>

#include "Yond_md5.h"
#include "Yond_drng.h"

#include "Poker.h"

#include "InfoParser.h"
#include "AgentInfo.h"

#include "MsgProcess.h"

#include "PlayerGoods.h"
#include "PlayerTasks.h"


#endif // _PUBLIC_H_INCLUDED_
