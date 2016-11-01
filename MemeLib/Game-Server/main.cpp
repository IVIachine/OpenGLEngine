#include "Game.h"
#include "EventSystem.h"
#include "NetServer.h"
#include "Input.h"

int main()
{
	Maths::seedRandom();

	NetServer::createInstance();

	bool isRunning = SERVER->setup();

	while (isRunning)
	{
		SERVER->update();
	}

	NetServer::destroyInstance();

	return 0;
}