#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <cassert>
#include <vec2.hpp>
#include <string>
#include <GL\glew.h>

#include "Vector2.h"
#include "DS_BytePool.h"
#include "Camera.h"

#define GRAPHICS Graphics::getInstance()

struct GLFWwindow;
class Texture2D;
class Sprite;
class Input;

class Graphics : public Trackable
{
public:
	static Graphics*	getInstance()
	{
		assert(sp_instance != nullptr);
		return sp_instance;
	};
	static Graphics*	createInstance()
	{
		sp_instance = new Graphics();
		return getInstance();
	};
	static void			destroyInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};

	bool		setup(int width, int height, std::string windowName);
	void		cleanup();

	int			getHeight();
	int			getWidth();	
	bool		isWindowOpen();

	void		clear();
	void		pollEvents();

	void		setWindowSize(const int width, const int height);
	void		setWindowTitle(const std::string title);
	void		flip();

	Vec2	getWindowSize();
	std::string	getWindowTitle();
	bool		exitWindow();

	GLfloat getLastY() { return m_lastY; };
	GLfloat getLastX() { return m_lastX; };

	void setLastX(GLfloat x) { m_lastX = x; };
	void setLastY(GLfloat y) { m_lastY = y; };

	Camera* getCamera() { return m_camera; };

	void	enableMouseLook(bool value) { m_enableMouseLook = value; };
	bool	isMouseLookEnabled() const { return m_enableMouseLook; };

private:
	Graphics();
	~Graphics();

	GLFWwindow* m_window;
	GLfloat m_lastX, m_lastY;

	Camera* m_camera;

	std::string m_title;
	int			m_width;
	int			m_height;
	Vec2	m_mousePosition;
	bool		m_enableMouseLook = false;

	
	static Graphics* sp_instance;

	friend class Keyboard;
};

#endif