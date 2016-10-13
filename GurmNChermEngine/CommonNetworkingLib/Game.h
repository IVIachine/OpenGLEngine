#ifndef _GAME_H_
#define _GAME_H_

#include "Texture2DManager.h"
#include "EventListener.h"
#include "NetClient.h"
#include "NetServer.h"
#include "UnitManager.h"
#include "GameController.h"

#include "ChatWindow.h"

#define GAME Game::getInstance()

const int NAME_LIMIT = 15;
const int MESSAGE_LIMIT = 75;

class Game : public EventListener
{
public:
	static Game*	getInstance();
	static Game*	createInstance();
	static void		destroyInstance();

	const static std::string ASSET_PATH;

	bool		setup(int width, int height);
	void		cleanup();
	
	void		loop();
	void		update();
	void		draw();
	
	virtual void handleEvent(const Event& ev);

private:
	Game();
	~Game();

	float		m_fps;
	bool 		m_isRunning;
	//bool		m_isLogin;
	TextField	m_loginField;
	ChatWindow	m_chat;
	Font		m_font;
	std::string m_addressString;
	static Game* sp_instance;
};

#endif