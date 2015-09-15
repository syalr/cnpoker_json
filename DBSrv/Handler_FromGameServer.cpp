#include "DBFactory.h"
#include "LoginQuery.h"
#include "GameQuery.h"
#include "Handler_FromGameServer.h"

Handler_FromGameServer::Handler_FromGameServer()
{

}

Handler_FromGameServer::~Handler_FromGameServer()
{

}

HANDLER_IMPL( Login_REQ )
{
	printf("Step2: <3> GD_Login_REQ\n");

	MSG_LOGIN_REQ * recvMsg = (MSG_LOGIN_REQ *)pMsg;

	TCHAR szQueryBuff[1024] = {0};
	snprintf( szQueryBuff, sizeof(szQueryBuff),
          " call p_Login(%d, \'%s\');",
          recvMsg->m_dwUserID,
          recvMsg->m_bySshKey );

    Query_Login * pQuery = Query_Login::ALLOC();
    if ( NULL != pQuery )
    {
        pQuery->SetQuery( szQueryBuff );
		Obj_db_passport.QueryDirect( pQuery );

        int nRet = pQuery->vctRes[0].m_iError;
		if ( nRet == 0 )
		{
            printf ( "UserID = %d, Port = %d, IP = %s \n",
                    pQuery->vctRes[0].m_uiStatus,
					pQuery->vctRes[0].m_uiServerID,
					pQuery->vctRes[0].m_uiGameType );

            memset(szQueryBuff, 0x0, sizeof(szQueryBuff) );
            snprintf( szQueryBuff, sizeof(szQueryBuff),
                    " call p_GamePacket(%d, %d );",
                    pQuery->vctRes[0].m_uiServerID,
                    pQuery->vctRes[0].m_uiGameType );

            Query_GamePacket_select *pGameQuery = Query_GamePacket_select::ALLOC();
            if ( NULL != pGameQuery )
            {
                pGameQuery->SetQuery( szQueryBuff );
                Obj_db_passport.QueryDirect( pGameQuery );

                nRet = pGameQuery->vctRes[0].m_iError;
                if ( nRet == 0 )
                {
                    printf ( "UserID = %d, Port = %d, IP = %s \n",
                            pGameQuery->vctRes[0].m_uiPoints,
                            pGameQuery->vctRes[0].m_uiWons,
                            pGameQuery->vctRes[0].m_uiFaileds,
                            pGameQuery->vctRes[0].m_uiAways );

                    MSG_LOGIN_ANC msg1;
                    msg1.m_dwUserID  = msg1.m_dwUserID;
                    msg1.m_wUserPort = recvMsg->m_wUserPort;
                    msg1.m_uiPoints  = pGameQuery->vctRes[0].m_uiPoints;
                    msg1.m_uiWons    = pGameQuery->vctRes[0].m_uiWons;
                    msg1.m_uiFaileds = pGameQuery->vctRes[0].m_uiFaileds;
                    msg1.m_uiAways   = pGameQuery->vctRes[0].m_uiAways;
                    pServerSession->Send( (BYTE*)&msg1, sizeof(msg1) );
                }
                else
                {
                    MSG_LOGIN_NAK msg2;
                    msg2.m_wUserPort  = recvMsg->m_wUserPort;
                    printf ( "Handler_FromGameServer::Login_REQ m_wUserPort = %d \n", recvMsg->m_wUserPort );
                    msg2.error = nRet;
                    pServerSession->Send( (BYTE*)&msg2, sizeof(msg2) );
                }
            }
		}
        else
        {
            MSG_LOGIN_NAK msg2;
			msg2.m_wUserPort  = recvMsg->m_wUserPort;
			printf ( "Handler_FromGameServer::Login_REQ m_wUserPort = %d \n", recvMsg->m_wUserPort );
			msg2.error = nRet;
			pServerSession->Send( (BYTE*)&msg2, sizeof(msg2) );
        }
    }

}

#if 0
HANDLER_IMPL( GD_Logout_REQ )
{
	MSG_GD_LOGOUT_REQ * pLogout = (MSG_GD_LOGOUT_REQ *)pMsg;
	// pLogout->uiRootID;

	GameServerSession * pSession = (GameServerSession *) pServerSession;
	DBUser * pUser = pSession->FindUser( pLogout->m_dwParameter );
	if (pUser != NULL) {
		DBFactory::Instance()->FreeDBUser(pUser);
		pSession->RemoveUser( pLogout->m_dwParameter );
	}
}

HANDLER_IMPL( GD_Save_CMD )
{
	MSG_GD_SAVE_CMD * pSave = (MSG_GD_SAVE_CMD *)pMsg;

	GameServerSession * pSession = (GameServerSession *) pServerSession;
	DBUser * pUser = pSession->FindUser( pSave->m_dwParameter );

	if (pUser != NULL)
	{
		pUser->GetGameInfo().m_uiScore 		= pSave->uiScore  ;
		pUser->GetGameInfo().m_uiFaileds 	= pSave->uiFaileds;
		pUser->GetGameInfo().m_uiWons 		= pSave->uiWons	  ;
		pUser->GetGameInfo().m_uiEscape 	= pSave->uiEscape ;

		MSG_GD_SAVE_ANC pANC;
		pANC.m_dwParameter = pSave->m_dwParameter;
		pServerSession->Send( (BYTE*)&pANC, sizeof(pANC) );
	}
}

HANDLER_IMPL( GD_Update_CMD )
{
	MSG_GD_UPDATE_CMD * pUpdate = (MSG_GD_UPDATE_CMD *)pMsg;

	GameServerSession * pSession = (GameServerSession *) pServerSession;
	DBUser * pUser = pSession->FindUser( pUpdate->m_dwParameter );

	if (pUser != NULL)
	{
		pUser->UpdateToDB();

		MSG_GD_UPDATE_ANC pANC;
		pANC.m_dwParameter = pUpdate->m_dwParameter;
		pServerSession->Send( (BYTE*)&pANC, sizeof(pANC) );
	}
}

#endif
