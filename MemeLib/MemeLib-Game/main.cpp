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
	bool isRunning = Game::createInstance()->setup(DISPLAY_WIDTH, DISPLAY_HEIGHT, &gameApp);
	
	if(!isRunning)
	{
		std::cout << "Failed to create game instance.\n";
		system("pause");
		return EXIT_FAILURE;
	}	
	while (isRunning)
	{
		GAME->beginStep();
		GAME->step();
		isRunning = GAME->endStep();
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