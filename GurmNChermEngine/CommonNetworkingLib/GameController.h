#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "Input.h"

#define CONTROLLER GameController::getInstance()

class GameController
{
public:
	static GameController*	getInstance();
	static GameController*	createInstance();
	static void				destroyInstance();

	virtual void update();

	void getKeyDown();
	void getClick();
	bool isDirection() { return mRequestingDirection; };
	std::string getCurrentDirection();
	void resetDirection();

private:
	GameController();
	~GameController();

	bool mPreviousMouseState, mCurrentMouseState;
	bool mPreviousKeyState, mCurrentKeyState;
	bool mRequestingDirection;
	std::string mKeyPressed, mMousePressed, mCurrentDirectionRequested;

	static GameController* sp_instance;

};



#endif