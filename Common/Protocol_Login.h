#ifndef _PROTOCOLCA_LOGIN_H_INCLUDED_
#define _PROTOCOLCA_LOGIN_H_INCLUDED_

#include "Protocol.h"

enum eLOGIN_PROTOCOL 
{
	// 预登陆
	Login_REQ			= 300,
	Login_ANC,
	Login_NAK,
};

#endif // _PROTOCOLCA_H_INCLUDED_