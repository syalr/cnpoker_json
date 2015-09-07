#ifndef _PACKAGESTRUCT_LOGIN_H_INCLUDED_
#define _PACKAGESTRUCT_LOGIN_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_Login.h"
#include "CommStruct.h"

#pragma pack(push, 1)

// Login Req
struct MSG_LOGIN_REQ : public MSG_BASE_FORWARD
{
	DWORD 	m_dwUserID;
	BYTE 	m_bySshKey[CODE_KEY_LEN+1];
	
	MSG_LOGIN_REQ() 
	{
		memset( this, 0, sizeof(MSG_LOGIN_REQ) );
		
		m_byCategory = Login_Protocol;
		m_byProtocol = Login_REQ;
	}
};

// Login Anc
struct MSG_LOGIN_ANC : public MSG_BASE_FORWARD
{
	PlayerInfo m_playerInfo;
	MSG_LOGIN_ANC() 
	{
		memset( this, 0, sizeof(MSG_LOGIN_ANC) );
		
		m_byCategory = Login_Protocol;
		m_byProtocol = Login_ANC;
	}
};

// Login Nak
struct MSG_LOGIN_NAK: public MSG_BASE_FORWARD
{
	WORD errorno;
	MSG_LOGIN_NAK() 
	{
		memset( this, 0, sizeof(MSG_LOGIN_NAK) );
		
		m_byCategory = Login_Protocol;
		m_byProtocol = Login_NAK;
	}
};

#pragma pack(pop)

#endif // _PACKAGESTRUCT_GA_H_INCLUDED_
