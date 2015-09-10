#ifndef _JSON_DISCARD_H_INCLUDED_
#define _JSON_DISCARD_H_INCLUDED_

class Json_Discard_REQ
{
	enum
	{
		eUNKNOWN 		= 0x00,
		eCOUNT          = 0x02,
		ePOKER          = 0x04,
	};

public:

	Json_Discard_REQ();
	~Json_Discard_REQ();

	int ParseJson( const char * pInput );

	MSG_DISCARDS_REQ * GetMsg(MSG_DISCARDS_REQ * pMsg);

private:

	MSG_DISCARDS_REQ msg;

	// ...
	DWORD   dwStatus;
};

#endif // _JSON_LOGINREQ_H_INCLUDED_
