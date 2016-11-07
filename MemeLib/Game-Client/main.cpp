#include "GameApp.h"
#include "Common.h"

const int DISPLAY_WIDTH = 1280, DISPLAY_HEIGHT = 720;

void printControls()
{
	std::cout
		<< "\t\t\tCONTROLS\n"
		<< "Press Enter key to unlock and lock camera\n"
		<< "Use mouse to look around(only when camera is unlocked)\n"
		<< "WASD to move\nQ and Z to move directly up and down\n"
		<< "P to delete units(if applicable) and spawn 10 new ones randomly\n"
		<< "F to have all units path to the target(floating dot)\n"
		<< "Up and Down arrow keys to change target location\n"
		<< "Press G to toggle debug mode\n";
}

int main()
{
	Maths::seedRandom();
	EventSystem::createInstance();
	GameApp gameApp;
	Game::createInstance();
	
	NetClient::createInstance();

	bool isRunning = 
		GAME->setup(DISPLAY_WIDTH, DISPLAY_HEIGHT, &gameApp) &&
		CLIENT->setup();

	if(!isRunning)
	{
		std::cout << "Failed to create game instance.\n";
		system("pause");
		return EXIT_FAILURE;
	}

	printControls();
	registerRPCs();

	while (isRunning)
	{
		GAME->beginStep();		
		GAME->step();

		CLIENT->update();
		isRunning = GAME->endStep();
	}
	
	UNITS->deleteAll();

	NetClient::destroyInstance();
	Game::destroyInstance();
	EventSystem::destroyInstance();

	return 0;
}