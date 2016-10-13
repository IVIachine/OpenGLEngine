#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_


#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <cassert>

#include "Camera.h"
#include "Font.h"
#include "RectShape.h"
#include "Sprite.h"
#include "Text.h"


#define GRAPHICS Graphics::getInstance()

class Graphics
{
public:
	static Graphics*	getInstance();
	static Graphics*	createInstance();
	static void			destroyInstance();

	void		setup(int width, int height, std::string windowName);
	void		cleanup();

	int			getHeight();
	int			getWidth();
	
	bool		isWindowOpen();

	void		clear();
	void		pollEvents();

	Vector2		mousePos();

	void		setFramerateLimit(unsigned int framerate);

	void		setWindowSize(const int width, const int height);
	void		setWindowTitle(const std::string title);

	Vector2		getWindowSize();
	std::string	getWindowTitle();

	Camera*		getCamera();
	void		setCamera(Camera& cam);
	void		resetCamera();
	
	void		draw(Sprite& sprite);
	void		draw(Font* fnt, std::string text, Vector2 pos, size_t size, Color color = Color::White);
	void		draw(Text& text);
	void		draw(RectShape& rect);

private:
	Graphics();
	~Graphics();

	sf::RenderWindow*	mp_sf_renderWindow;
	sf::Event			m_sf_event;

	std::string m_title;
	int			m_width;
	int			m_height;
	Vector2		m_mousePosition;
	Camera		m_camera;

	static char s_getChar;

	static Graphics* sp_instance;

	friend class GameController;
	friend class Input;
};

#endif