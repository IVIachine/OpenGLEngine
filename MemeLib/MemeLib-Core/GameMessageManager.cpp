#include <list>

#include "Game.h"
#include "GameMessageManager.h"
#include "GameMessage.h"

GameMessageManager* GameMessageManager::sp_instance = NULL;

using namespace std;

GameMessageManager::GameMessageManager()
{
}

GameMessageManager::~GameMessageManager()
{
	clear();
}


bool GameMessageManager::setup()
{
	return true;
}

void GameMessageManager::clear()
{
	list<GameMessage*>::iterator iter;
	for (iter = mMessages.begin(); iter != mMessages.end(); ++iter)
	{
		delete (*iter);
	}
}



void GameMessageManager::processMessagesForThisframe()
{
	float currentTime = TIME->getCurrentTime();

	list<GameMessage*>::iterator iter = mMessages.begin();
	while( iter != mMessages.end() )
	{
		if( (*iter)->getScheduledTime() <= currentTime )
		{
			(*iter)->process();
			delete (*iter);
			iter = mMessages.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void GameMessageManager::addMessage( GameMessage* pMessage, int delay )
{
	float currentTime = TIME->getCurrentTime();

	//set frame numbers
	pMessage->mSubmittedTime = currentTime;
	pMessage->mScheduledTime = currentTime + delay;

	//put it in the message list
	mMessages.push_back( pMessage );
}