#include <iostream>
#include "GameApp.h"
#include "EventSystem.h"
#include "Mesh.h"
#include "Shader.h"
#include "Graphics.h"
#include "MemoryTracker.h"

const int DISPLAY_WIDTH = 1280, DISPLAY_HEIGHT = 720;

int main()
{
	GameApp gameApp;

	EventSystem::createInstance();

	if(!Game::createInstance()->setup(DISPLAY_WIDTH, DISPLAY_HEIGHT))
	{
		std::cout << "Failed to create game instance.\n";
		system("pause");
		return EXIT_FAILURE;
	}
	else
	{
		gameApp.setup(DISPLAY_WIDTH, DISPLAY_HEIGHT);

		bool isRunning = gameApp.loadResources();
		while (isRunning)
		{
			gameApp.update();

			gameApp.draw();

			isRunning = GAME->endStep();
		}

		gameApp.cleanup();
	}
	Game::destroyInstance();

	EventSystem::destroyInstance();
	
	gMemoryTracker.reportAllocations(std::cout);
	//system("pause");

	return 0;
}