#include "Graphics.h"
#include <iostream>
#include "Game.h"

char Graphics::s_getChar = '\0';
Graphics* Graphics::sp_instance = NULL;

static GLfloat yaw;
static GLfloat pitch;
bool firstMouse = true;
void mouse_callback(GLFWwindow * window, double xpos, double ypos);

Graphics::Graphics()
{
	m_width = 0;
	m_height = 0;
	m_window = NULL;
	m_lastX = m_width / 2;
	m_lastY = m_height / 2;
}

Graphics::~Graphics()
{
	cleanup();
}

void Graphics::moveCamera(Camera* camera)
{
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_keys[GLFW_KEY_W] = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_keys[GLFW_KEY_S] = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_keys[GLFW_KEY_A] = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_keys[GLFW_KEY_D] = true;
	}

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_RELEASE)
	{
		m_keys[GLFW_KEY_W] = false;
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_RELEASE)
	{
		m_keys[GLFW_KEY_S] = false;
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_RELEASE)
	{
		m_keys[GLFW_KEY_A] = false;
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_RELEASE)
	{
		m_keys[GLFW_KEY_D] = false;
	}


	float cameraSpeed = .1;
	if (m_keys[GLFW_KEY_W])
	{
		camera->setPos(camera->getPos() + cameraSpeed * camera->getFowardVector());
	}
	if (m_keys[GLFW_KEY_S])
	{
		camera->setPos(camera->getPos() - cameraSpeed * camera->getFowardVector());
	}
	if (m_keys[GLFW_KEY_A])
	{
		camera->setPos(camera->getPos() - glm::normalize(glm::cross(camera->getFowardVector(), camera->getUpVector())) * cameraSpeed);
	}
	if (m_keys[GLFW_KEY_D])
	{
		camera->setPos(camera->getPos() + glm::normalize(glm::cross(camera->getFowardVector(), camera->getUpVector())) * cameraSpeed);
	}


}


Graphics* Graphics::getInstance()
{
	assert(sp_instance != nullptr);
	return sp_instance;
}

Graphics* Graphics::createInstance()
{
	sp_instance = new Graphics();
	return getInstance();
}

void Graphics::destroyInstance()
{
	delete sp_instance;
	sp_instance = NULL;
}


void Graphics::setup(int width, int height, std::string windowName)
{
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
		glfwTerminate();
		std::cout << "Failed to load the window, exiting...\n";
		system("pause");
		exit(1);
	}

	glfwMakeContextCurrent(m_window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glfwSetCursorPosCallback(m_window, mouse_callback);
	mouse_callback(m_window, 0, 0);
}

void Graphics::cleanup()
{
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


glm::vec2 Graphics::getWindowSize()
{
	return glm::vec2((float)m_width, (float)m_height);
}

std::string Graphics::getWindowTitle()
{
	return m_title;
}

bool Graphics::exitWindow()
{
	return glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse) // this bool variable is initially set to true
	{
		GRAPHICS->setLastX(xpos);
		GRAPHICS->setLastY(ypos);
		firstMouse = false;
	}

	GLfloat xoffset = xpos - GRAPHICS->getLastX();
	GLfloat yoffset = GRAPHICS->getLastY() - ypos; // Reversed since y-coordinates range from bottom to top
	GRAPHICS->setLastX(xpos);
	GRAPHICS->setLastY(ypos);
	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	
	Game::getInstance()->getCamera()->setFront(glm::normalize(front));
}
