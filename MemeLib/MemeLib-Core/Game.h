#ifndef _GAME_H_
#define _GAME_H_

#include "EventListener.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Texture2D.h"
#include "GameTime.h"
#include "Volume.h"
#include "ResourceManager.h"
#include "Maths.h"

#define GAME Game::getInstance()

const float LOOP_TARGET_TIME = GameTime::FPS_60;
const float FIXED_UPDATE_DELTA = LOOP_TARGET_TIME / 1000.0f;

class Application;

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

	bool	setup(int width, int height, Application* pApp);
	void	clear();
	
	void	beginStep();
	void	step();
	bool	endStep();	

	void handleEvent(const Event& ev) override;

	void stop() { m_stopRequested = true; }

	Application* getApp() const { return mp_app; };

protected:
	Game();
	~Game();
private:
	float	m_fps = GameTime::FPS_60;
	bool 	m_isRunning;
	bool	m_stopRequested = false;

	Application* mp_app;

	static Game* sp_instance;
};



#endif