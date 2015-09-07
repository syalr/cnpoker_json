#include <Utility.h>
#include <iostream>
#include <Common.h>
#include "Yond_json.h"
#include "Json_LoginREQ.h"

using std::cout;
using std::endl;

Json_LoginREQ::Json_LoginREQ()
{
	dwStatus = 0;
}


Json_LoginREQ::~Json_LoginREQ()
{
	
}

int Json_LoginREQ::ParseJson( const char * pInput )
{
	dwStatus = 0;
	
	cJSON * root = NULL;
	
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}
	
	int nLen = 0;
	
	// user id
	cJSON * uid = cJSON_GetObjectItem( root, "uid" );
	if ( uid ) {
		dwStatus |= eUSERID;
		msg.m_dwUserID = uid->valueint;
	}

	// User SshKey
	cJSON * sshkey = cJSON_GetObjectItem( root, "sshkey" );
	if ( sshkey ) {
		dwStatus |= eSSHKEY;
		nLen = strlen( sshkey->valuestring );
		if ( nLen < sizeof(msg.m_bySshKey) )
		{
			memcpy( msg.m_bySshKey, sshkey->valuestring, nLen + 1 );
			msg.m_bySshKey[ nLen ] = '\0';
		}
	}

	//// game id
	//cJSON * gameid = cJSON_GetObjectItem( root, "gameid" );
	//if ( gameid ) {
	//	dwStatus |= eGAMEID;
	//	msg.m_dwGameID = gameid->valueint;
	//}
		
	if ( root ) {
		cJSON_Delete( root );
	}
	
	// 数据是否完整
	if ( dwStatus != eALLINFO ) {
		printf("[Json_LoginREQ] Information not enought.\n");
		return -1;
	}
	
	return 0;
}
	
MSG_LOGIN_REQ * Json_LoginREQ::GetMsg(MSG_LOGIN_REQ * pMsg)
{
	if ( dwStatus & 0x48)
	{	
		//msg.m_dwLoginType = JSON_SERVER;
		memcpy( pMsg, &msg, sizeof(msg) );
		return pMsg;
	}
	return NULL;
}

