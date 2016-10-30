#include <iostream>
#include "GameApp.h"
#include "EventSystem.h"
#include "Mesh.h"
#include "Shader.h"
#include "Graphics.h"
#include "MemoryTracker.h"
#include <sstream>
#include <time.h>

const int DISPLAY_WIDTH = 1280, DISPLAY_HEIGHT = 720;

int main()
{
	srand((unsigned)time(NULL));
	EventSystem::createInstance();
	GameApp gameApp;
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
		UNITS->deleteAll();
		gameApp.cleanup();
	}

	Game::destroyInstance();
	EventSystem::destroyInstance();


	// Don't pause unless there're leaks
	std::stringstream stream;
	gMemoryTracker.reportAllocations(stream);
	if (stream.str().size() > 0)
	{
		std::cout
			<< "Current memory allocations:\n"
			<< stream.str();

		system("pause");
	}
	else
	{
		std::cout 
			<< "There are no memory allocations.\n";
	}

	return 0;
}