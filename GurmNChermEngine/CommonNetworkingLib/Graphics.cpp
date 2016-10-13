#include "Graphics.h"
#include "SFML\Window\Event.hpp"

char Graphics::s_getChar = '\0';
Graphics* Graphics::sp_instance = NULL;

Graphics::Graphics()
{
	m_width = 0;
	m_height = 0;
	mp_sf_renderWindow = NULL;
}

Graphics::~Graphics()
{
	cleanup();
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
	mp_sf_renderWindow = new sf::RenderWindow(
		sf::VideoMode(width, height), windowName);
}

void Graphics::cleanup()
{
	//mDisplay->~RenderWindow;
}


void Graphics::setFramerateLimit(unsigned int framerate)
{
	mp_sf_renderWindow->setFramerateLimit(framerate);
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
	return mp_sf_renderWindow->isOpen();
}


void Graphics::clear()
{
	mp_sf_renderWindow->display();
	mp_sf_renderWindow->clear(sf::Color::Black);
}

void Graphics::pollEvents()
{
	sf::Event ev;

	while (mp_sf_renderWindow->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
		{
			mp_sf_renderWindow->close();
		}
		break;
		case sf::Event::TextEntered:
		{
			if (ev.text.unicode < 128)
			{
				s_getChar = static_cast<char>(ev.text.unicode);
			}
		}
		break;
		default:
		break;
		}
	}
}

Vector2 Graphics::mousePos()
{
	if (m_sf_event.type == sf::Event::MouseMoved)
	{
		m_mousePosition = Vector2(
			(float)sf::Mouse::getPosition(*(mp_sf_renderWindow)).x,
			(float)sf::Mouse::getPosition(*(mp_sf_renderWindow)).y);
	}

	return m_mousePosition;
}


void Graphics::setWindowSize(const int width, const int height)
{
	mp_sf_renderWindow->setSize(sf::Vector2u(width, height));
}

void Graphics::setWindowTitle(const std::string title)
{
	mp_sf_renderWindow->setTitle(title);
}


Vector2 Graphics::getWindowSize()
{
	return Vector2((float)m_width, (float)m_height);
}

std::string Graphics::getWindowTitle()
{
	return m_title;
}


Camera* Graphics::getCamera()
{
	return &m_camera;
}

void Graphics::setCamera(Camera& cam)
{
	m_camera = cam;
	mp_sf_renderWindow->setView(m_camera.mView_sf);
}

void Graphics::resetCamera()
{
	mp_sf_renderWindow->setView(mp_sf_renderWindow->getDefaultView());
	m_camera.mView_sf = mp_sf_renderWindow->getView();
}


void Graphics::draw(Sprite& sprite)
{
	mp_sf_renderWindow->draw(sprite.m_sf_sprite);
}

void Graphics::draw(Text& text)
{
	mp_sf_renderWindow->draw(text.mText_sf);
}

void Graphics::draw(Font* fnt, std::string text, Vector2 pos, size_t size, Color color)
{
	draw(Text(fnt, text, size, Text::Style::Regular, color, pos));
}

void Graphics::draw(RectShape& rect)
{
	mp_sf_renderWindow->draw(rect.m_sf_rectangleShape);
}