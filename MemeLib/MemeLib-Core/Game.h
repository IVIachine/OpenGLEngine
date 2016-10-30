#ifndef _GAME_H_
#define _GAME_H_

#include "EventListener.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Texture2D.h"
#include "GameTime.h"
#include "Volume.h"
#include "ResourceManager.h"

#define GAME Game::getInstance()

const float LOOP_TARGET_TIME = GameTime::FPS_60;

class Game : public EventListener
{
public:
	static Game*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static Game*	createInstance()
	{
		sp_instance = new Game();
		return getInstance();
	};
	static void		destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	bool	setup(int width, int height);
	void	cleanup();
	
	void	beginStep();
	void	step();
	bool	endStep();	

	virtual void handleEvent(const Event& ev);

protected:
	Game();
	~Game();
private:
	float	m_fps = GameTime::FPS_60;
	bool 	m_isRunning;
	bool	m_stopRequested = false;

	static Game* sp_instance;
};



#endif