#include "GameApp.h"
#include "PongApp.h"
#include "Common.h"
#include "TextAsset.h"

const int DISPLAY_WIDTH = 1280, DISPLAY_HEIGHT = 720;

int main()
{
	Maths::seedRandom();
	EventSystem::createInstance();
	Game::createInstance();	
	NetClient::createInstance();

	PongApp app;

	bool isRunning = 
		GAME->setup(DISPLAY_WIDTH, DISPLAY_HEIGHT, &app) &&
		CLIENT->setup();

	if(!isRunning)
	{
		std::cout << "Failed to create game instance.\n";
		system("pause");
		return EXIT_FAILURE;
	}

	TextAsset helpText("../Assets/data/help.txt");
	helpText.display();

	registerRPCs();

	while (isRunning)
	{
		GAME->beginStep();		
		GAME->step();
		CLIENT->update();
		isRunning = GAME->endStep();
	}

	NetClient::destroyInstance();
	Game::destroyInstance();
	EventSystem::destroyInstance();

	return 0;
}