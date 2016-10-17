#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <cassert>
#include "vec2.hpp"
#include <string>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "DS_BytePool.h"
#include "Camera.h"

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

	void		setWindowSize(const int width, const int height);
	void		setWindowTitle(const std::string title);
	void		flip();
	glm::vec2	getWindowSize();
	std::string	getWindowTitle();
	bool		exitWindow();
	void moveCamera(Camera* camera);
	GLfloat getLastY() { return m_lastY; };
	GLfloat getLastX() { return m_lastX; };
	void setLastX(GLfloat x) { m_lastX = x; };
	void setLastY(GLfloat y) { m_lastY = y; };

private:
	Graphics();
	~Graphics();

	GLFWwindow* m_window;
	GLfloat m_lastX, m_lastY;
	//Texture* test;

	std::string m_title;
	int			m_width;
	int			m_height;
	glm::vec2	m_mousePosition;
	static char s_getChar;
	bool m_keys[1024];
	static Graphics* sp_instance;
};

#endif