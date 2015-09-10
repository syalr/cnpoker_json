#ifndef _JSON_LOGIN_REQ_H_INCLUDED_
#define _JSON_LOGIN_REQ_H_INCLUDED_

class Json_Login_REQ
{
	enum
	{
		eUNKNOWN 		= 0x00,
		eUSERID			= 0x01,
		eSSHKEY 		= 0x02,
		eALLINFO 		= 0x03,
	};

public:

	Json_Login_REQ();
	~Json_Login_REQ();

	int ParseJson( const char * pInput );

	MSG_LOGIN_REQ * GetMsg(MSG_LOGIN_REQ * pMsg);

private:

	MSG_LOGIN_REQ msg;

	// ...
	DWORD   dwStatus;
};

#endif // _JSON_LOGINREQ_H_INCLUDED_
