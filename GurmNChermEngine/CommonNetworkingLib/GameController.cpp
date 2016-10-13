#include "GameController.h"
#include "EventSystem.h"
#include "Game.h"

GameController* GameController::sp_instance = NULL;

GameController::GameController()
{
}

GameController::~GameController()
{
}


GameController* GameController::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void GameController::destroyInstance()
{
	delete sp_instance;
	sp_instance = NULL;
}

GameController* GameController::createInstance()
{
	sp_instance = new GameController();
	return getInstance();
}


void GameController::getKeyDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mKeyPressed = "Up";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mKeyPressed = "Down";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mKeyPressed = "Left";
		mCurrentKeyState = true;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mKeyPressed = "Right";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		mKeyPressed = "D";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		mKeyPressed = "A";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mKeyPressed = "W";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		mKeyPressed = "S";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mKeyPressed = "Escape";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		mKeyPressed = "1";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		mKeyPressed = "2";
		mCurrentKeyState = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		mKeyPressed = "X";
		mCurrentKeyState = true;
	}

	if (mKeyPressed == "")
	{
		mCurrentKeyState = false;
	}

	if (mPreviousKeyState && !mCurrentKeyState)
	{

	}
	else if (mCurrentKeyState)
	{
		if (mKeyPressed == "Escape")
		{
		}
		if (mKeyPressed == "1" || mKeyPressed == "2")
		{
		}

		if (mKeyPressed == "W")
		{
			mCurrentDirectionRequested += "Up";
			mRequestingDirection = true;
		}
		if (mKeyPressed == "A")
		{
			mCurrentDirectionRequested += "Left";
			mRequestingDirection = true;
		}
		if (mKeyPressed == "S")
		{
			mCurrentDirectionRequested += "Down";
			mRequestingDirection = true;
		}
		if (mKeyPressed == "D")
		{
			mCurrentDirectionRequested += "Right";
			mRequestingDirection = true;
		}

		mKeyPressed = "";
	}

	mPreviousKeyState = mCurrentKeyState;
}

void GameController::getClick()
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mMousePressed = "Left";
		mCurrentMouseState = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		mMousePressed = "Right";
		mCurrentMouseState = true;
	}
	else
	{
		mCurrentMouseState = false;
	}

	if (mPreviousMouseState == true && mCurrentMouseState == false)
	{
		if (mMousePressed == "Left")
		{
			
		}
		//else if (mMousePressed == "Right")
		//gpEventSystem->fireEvent(DeleteEvent(mState.x, mState.y));
		mMousePressed = "";
	}
	mPreviousMouseState = mCurrentMouseState;
}

std::string GameController::getCurrentDirection()
{
	return mCurrentDirectionRequested;
}

void GameController::resetDirection()
{
	mRequestingDirection = false;
	mCurrentDirectionRequested = "";
}


void GameController::update()
{
	getKeyDown();
	getClick();
}