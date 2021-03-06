#include "Graphics.h"
#include <iostream>
#include "Game.h"
#include "Input.h"
#include "Sprite.h"

Graphics* Graphics::sp_instance = NULL;

static GLfloat yaw;
static GLfloat pitch;

void mouse_look(GLFWwindow * window, double xpos, double ypos)
{
	GLfloat xoffset = GLfloat(xpos) - GRAPHICS->getLastX();
	GLfloat yoffset = GRAPHICS->getLastY() - GLfloat(ypos);
	
	GRAPHICS->setLastX(GLfloat(xpos));
	GRAPHICS->setLastY(GLfloat(ypos));
	
	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	Vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	if (GRAPHICS->isMouseLookEnabled())
	{
		GRAPHICS->getCamera()->setForward(glm::normalize(front));
	}
	else
	{
		//GRAPHICS->getCamera()->setForward(Vec3(0, 0, 1));
	}
}


Graphics::Graphics()
{
	m_width = 0;
	m_height = 0;
	m_window = NULL;
	m_lastX = GLfloat(m_width / 2);
	m_lastY = GLfloat(m_height / 2);
}

Graphics::~Graphics()
{
	cleanup();
}


bool Graphics::setup(int width, int height, std::string windowName)
{
	Vec3 camPos = { 0.0f, 1.0f, -1.0f };
	m_camera = new Camera(camPos, 70.0f, float(width) / float(height), 0.01f, 1000.0f);

	m_width = width;
	m_height = height;

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw, exiting...\n";
		system("pause");
		exit(1);
	}

	m_window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

	if (!m_window)
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glfwSetCursorPosCallback(m_window, mouse_look);
	mouse_look(m_window, 0, 0);

	return true;
}

void Graphics::cleanup()
{
	delete m_camera;
	m_camera = NULL;
}


int Graphics::getHeight()
{
	return m_height;
}

int Graphics::getWidth()
{
	return m_width;
}

bool Graphics::isWindowOpen()
{
	return !glfwWindowShouldClose(m_window);
}


void Graphics::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::pollEvents()
{
	if (m_showMouse)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	glfwPollEvents();
}


void Graphics::setWindowSize(const int width, const int height)
{
	glfwSetWindowSize(m_window, width, height);
}

void Graphics::setWindowTitle(const std::string title)
{
	glfwSetWindowTitle(m_window, title.c_str());
}

void Graphics::flip()
{
	glfwSwapBuffers(m_window);
}

void Graphics::toggleMouse()
{
	m_showMouse = !m_showMouse;
}


Vec2 Graphics::getWindowSize()
{
	return Vec2((float)m_width, (float)m_height);
}

std::string Graphics::getWindowTitle()
{
	return m_title;
}

bool Graphics::exitWindow()
{
	return glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}