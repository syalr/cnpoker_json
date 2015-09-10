#ifndef _GameTableList_H_INCLUDED_
#define _GameTableList_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "ServerSession.h"
#include "GameTable.h"

class GameTableList : public Double_List_T<GameTable>
{
public:
	GameTableList();
	virtual ~GameTableList();

	void Clear();

	inline void Lock() { m_cs.Lock(); }
	inline void Unlock() { m_cs.Unlock(); }

private:
	Yond_mutex m_cs;
};

typedef GameTableList				GAMETABLE_LIST;
typedef GameTableList::iterator		GAMETABLE_LIST_ITER;

#endif // _GAMEUSERMANAGER_H_INCLUDED_

