#ifndef _JSON_LOGINREQ_H_INCLUDED_
#define _JSON_LOGINREQ_H_INCLUDED_

class Json_LoginREQ
{
	enum
	{
		eUNKNOWN 		= 0x00,
		eUSERID			= 0x01,
		eSSHKEY 		= 0x02,
		eALLINFO 		= 0x03,
	};

public:

	Json_LoginREQ();
	~Json_LoginREQ();

	int ParseJson( const char * pInput );
	
	MSG_LOGIN_REQ * GetMsg(MSG_LOGIN_REQ * pMsg); 
	
private:

	MSG_LOGIN_REQ msg;
	
	// ...
	DWORD   dwStatus;
};

#endif // _JSON_LOGINREQ_H_INCLUDED_