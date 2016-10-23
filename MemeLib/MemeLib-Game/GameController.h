#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include <string>
#include <fstream>
#include "Trackable.h"

class GameController : public Trackable
{
public:
	static void processInput();

private:
	GameController() {}
	~GameController() {}
};

#endif // !_GAME_CONTROLLER_H_
