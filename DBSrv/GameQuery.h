#ifndef __GAMEQUERY_H_INCLUDED__
#define __GAMEQUERY_H_INCLUDED__

#include <dbCommon.h>

class Query_GamePacket_select : public QueryResult
{
	_DECLARE_QUERY_POOL(Query_GamePacket_select);

public:

	enum
	{
		RESULT_COL_NUM = 4,
		PARAM_COL_NUL = 2,
	};

	struct sRESULT
	{
                 int m_iError;
		unsigned int m_uiPoints; 		// 分数
		unsigned int m_uiWons; 		    // 失败次数
		unsigned int m_uiFaileds; 		// 赢的次数
		unsigned int m_uiAways; 		// 逃跑次数

		sRESULT()
		{
			m_uiPoints	    = 0;
			m_uiWons        = 0;
			m_uiFaileds     = 0;
			m_uiAways       = 0;
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

	_BEGIN_BINDING_DATA( sRESULT, vctRes, uLength, 1, RESULT_COL_NUM )
		_BINDING_COLUMN(0, m_uiPoints)
		_BINDING_COLUMN(1, m_uiWons)
		_BINDING_COLUMN(2, m_uiFaileds)
		_BINDING_COLUMN(3, m_uiAways)
	_END_BINDING_DATA()

	struct tag_LOGIN {
		unsigned int m_uiUserID;
		unsigned int m_uiGameID;
	} pParam[1];

	_BEGIN_PARAM_DATA( tag_LOGIN, pParam, PARAM_COL_NUL )
		_BINDING_PARAM(0, m_uiUserID,  SQL_PARAM_INPUT)
		_BINDING_PARAM(1, m_uiGameID,  SQL_PARAM_INPUT)
	_END_PARAM_DATA()
};


class Query_GamePackage_update : public QueryResult
{
	_DECLARE_QUERY_POOL(Query_GamePackage_update);

public:

	enum
	{
		RESULT_COL_NUM  = 1,
		PARAM_COL_NUL   = 5,
	};

	struct sRESULT {
		unsigned int m_iError;
		sRESULT() {
			m_iError = 0;
		}
	};

	ULONG uLength[RESULT_COL_NUM];
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
	_END_BINDING_DATA()

	struct tag_LOGIN {
		unsigned int m_uiUserID;
		unsigned int m_uiPoints;
		unsigned int m_uiWons;
		unsigned int m_uiFaileds;
		unsigned int m_uiAways;
	} pParam[1];

	_BEGIN_PARAM_DATA(tag_LOGIN, pParam, PARAM_COL_NUL)
		_BINDING_PARAM(0, m_uiUserID,  	SQL_PARAM_INPUT)
		_BINDING_PARAM(1, m_uiPoints,  	SQL_PARAM_INPUT)
		_BINDING_PARAM(2, m_uiWons,     SQL_PARAM_INPUT)
		_BINDING_PARAM(3, m_uiFaileds,  SQL_PARAM_INPUT)
		_BINDING_PARAM(4, m_uiAways,  	SQL_PARAM_INPUT)
	_END_PARAM_DATA()
};

#endif
