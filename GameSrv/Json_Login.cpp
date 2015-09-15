#include <Utility.h>
#include <iostream>
#include <Common.h>
#include "Yond_json.h"
#include "Json_Login.h"

using std::cout;
using std::endl;

Json_Login_REQ::Json_Login_REQ()
{
	dwStatus = 0;
}


Json_Login_REQ::~Json_Login_REQ()
{

}

int Json_Login_REQ::ParseJson( const char * pInput )
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

MSG_LOGIN_REQ * Json_Login_REQ::GetMsg(MSG_LOGIN_REQ * pMsg)
{
	if ( dwStatus & 0x48)
	{
		//msg.m_dwLoginType = JSON_SERVER;
		memcpy( pMsg, &msg, sizeof(msg) );
		return pMsg;
	}
	return NULL;
}



/*
 *  应答
 */
Json_Login_ANC::Json_Login_ANC()
{
}


Json_Login_ANC::~Json_Login_ANC()
{

}

void Json_Login_ANC::SetMsg(MSG_LOGIN_ANC * pMsg)
{
	if ( pMsg != NULL ) {
		memcpy( &msg, pMsg, sizeof(msg) );
	}
}

WORD Json_Login_ANC::GetJson(char * szJson, WORD wSize )
{
	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
						"\"point\":\"%d\","
						"\"wons\":\"%d\","
						"\"faileds\":\"%d\","
						"\"aways\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         msg.m_dwUserID,
         msg.m_uiPoints,
         msg.m_uiWons,
         msg.m_uiFaileds,
         msg.m_uiAways);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(szJson, buff, len);
	}
	return len;
}
