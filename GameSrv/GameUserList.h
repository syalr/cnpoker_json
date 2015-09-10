#ifndef _GameUserList_H_INCLUDED_
#define _GameUserList_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "ServerSession.h"
#include "GameUser.h"

class GameUserList : public Double_List_T<GameUser>
{
public:
	GameUserList();
	~GameUserList();

    void Clear();

	inline void Lock() { m_cs.Lock(); }
	inline void Unlock() { m_cs.Unlock(); }

private:
	Yond_mutex m_cs;
};

typedef GameUserList				GAMEUSER_LIST;
typedef GameUserList::iterator		GAMEUSER_LIST_ITER;

#endif // _GameUserList_H_INCLUDED_

