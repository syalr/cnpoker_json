#include "GameUserList.h"


GameUserList::GameUserList()
{

}

GameUserList::~GameUserList()
{
}


void GameUserList::Clear()
{
	GAMEUSER_LIST_ITER it;

	GameUser *pUser;

	this->Lock();

	while ( !this->empty() )
	{
		pUser = this->pop_front();

		if ( pUser )
			delete pUser;
	}

	Unlock();
}
