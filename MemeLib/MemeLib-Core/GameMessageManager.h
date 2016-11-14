#ifndef _GAME_MESSAGE_MANAGER_H_
#define _GAME_MESSAGE_MANAGER_H_

#include <list>
#include <Trackable.h>
#include <cassert>

#define MESSAGES GameMessageManager::getInstance()

class GameMessage;

class GameMessageManager : public Trackable
{
public:
	static GameMessageManager*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static GameMessageManager*	createInstance()
	{
		sp_instance = new GameMessageManager();
		return getInstance();
	};
	static void					destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	bool	setup();
	void	clear();

	//note - message manager will now "own" the message and will delete it at its pleasure
	void addMessage(GameMessage* pMessage, int delay = 0);
	void processMessagesForThisframe();

private:
	GameMessageManager();
	~GameMessageManager();

	std::list<GameMessage*> mMessages;

	static GameMessageManager* sp_instance;
};

#endif