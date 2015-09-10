#include "GameTableList.h"


GameTableList::GameTableList()
{

}

GameTableList::~GameTableList()
{
}

void GameTableList::Clear()
{
	GAMETABLE_LIST_ITER it;

	GameTable * pTable;

	this->Lock();

	while ( !this->empty() )
	{
		pTable = this->pop_front();

		if ( pTable )
			delete pTable;
	}

	Unlock();
}
