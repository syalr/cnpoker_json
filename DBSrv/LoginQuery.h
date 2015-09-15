#ifndef __LOGIN_QUERY_H_INCLUDED__
#define __LOGIN_QUERY_H_INCLUDED__

#include <dbCommon.h>

#pragma pack(push,1)

class Query_Login : public QueryResult
{
	_DECLARE_QUERY_POOL( Query_Login );

public:

	enum
	{
		RESULT_COL_NUM = 2,
		PARAM_COL_NUL  = 4,
	};

	struct sRESULT {
                 int m_iError;
		unsigned int m_uiStatus;
		unsigned int m_uiServerID;
		unsigned int m_uiGameType;
		char m_szIP[16];

		sRESULT()
		{
			memset( this, 0, sizeof(sRESULT) );
		}
	};

	ULONG uLength[RESULT_COL_NUM]; // 4

	vector<sRESULT> vctRes;

	void AllocData()
	{
		sRESULT m_RESULT;
		memset(&m_RESULT, 0, sizeof( m_RESULT) );
		vctRes.push_back( m_RESULT );
	}

	void InitData() { vctRes.clear(); }
	void dealData() { vctRes.pop_back(); }

	_BEGIN_BINDING_DATA( sRESULT, vctRes, uLength, 1, RESULT_COL_NUM)
        _BINDING_COLUMN(0, m_iError)
		_BINDING_COLUMN(1, m_uiStatus)
		_BINDING_COLUMN(2, m_uiServerID)
		_BINDING_COLUMN(3, m_uiGameType)
	_END_BINDING_DATA()

	struct tag_LOGIN {
		unsigned int m_nUserID;
		BYTE m_byPreSSHKey[33];
	} pParam[1];

	_BEGIN_PARAM_DATA(tag_LOGIN, pParam, PARAM_COL_NUL)
		_BINDING_PARAM(0, m_nUserID,  SQL_PARAM_INPUT)
		_BINDING_PARAM_PTR(1, m_byPreSSHKey,  SQL_PARAM_INPUT)
	_END_PARAM_DATA()
};

#pragma pack(pop)

#endif // __PRELOGIN_QUERY_H_INCLUDED__
