#include <Utility.h>
#include <iostream>
#include <Common.h>
#include <Public.h>
#include "Yond_json.h"
#include "Json_Discard.h"

using std::cout;
using std::endl;

Json_Discard_REQ::Json_Discard_REQ()
{
	dwStatus = 0;
}


Json_Discard_REQ::~Json_Discard_REQ()
{

}

int Json_Discard_REQ::ParseJson( const char * pInput )
{
	dwStatus = 0;

	cJSON * root = NULL;

	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	int nLen = 0;

	// user id
	cJSON * js_count = cJSON_GetObjectItem( root, "count" );
	if ( js_count ) {
		dwStatus |= eCOUNT;
		msg.uiSize = js_count->valueint;
	}

	// User SshKey
	cJSON * js_poker = cJSON_GetObjectItem( root, "poker" );
	if ( js_poker ) {
		dwStatus |= ePOKER;
		Yond_string szPoker(js_poker->valuestring);
		memset( msg.byDiscards, 0x0, sizeof(msg.byDiscards) );
		szPoker.GetByteArray(msg.byDiscards, sizeof(msg.byDiscards), ',');
	}

	if ( root ) {
		cJSON_Delete( root );
	}

	return 0;
}

MSG_DISCARDS_REQ * Json_Discard_REQ::GetMsg(MSG_DISCARDS_REQ * pMsg)
{
	if ( msg.uiSize > 0)
	{
		//msg.m_dwLoginType = JSON_SERVER;
		memcpy( pMsg, &msg, sizeof(msg) );
		return pMsg;
	}
	return NULL;
}

