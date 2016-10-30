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
	std::cout << "\t\t\tCONTROLS\nPress Enter key to unlock and lock camera\nUse mouse to look around(only when camera is unlocked)\nWASD to move\nQ and Z to move directly up and down\nP to delete units(if applicable) and spawn 10 new ones randomly\nF to have all units path to the target(floating dot)\nUp and Down arrow keys to change target location\n";
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
	
	UNITS->deleteAll();

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