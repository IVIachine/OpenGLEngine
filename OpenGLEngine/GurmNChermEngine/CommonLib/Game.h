#ifndef _GAME_H_
#define _GAME_H_

#include "EventListener.h"
#include "Graphics.h"
#include "Image.h"

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
	Camera* getCamera() { return m_camera; };
	virtual void handleEvent(const Event& ev);

private:
	Game();
	~Game();

	std::vector<Image*> m_Images;
	float		m_fps;
	bool 		m_isRunning;
	std::string m_addressString;
	static Game* sp_instance;
	Camera* m_camera;
	float m_counter;
	Image* m_skybox;
};

#endif