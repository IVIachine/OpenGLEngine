#include <iostream>
#include "Game.h"
#include "EventSystem.h"
#include "Mesh.h"
#include "Shader.h"
#include "Graphics.h"
const int DISPLAY_WIDTH = 1280, DISPLAY_HEIGHT = 720;

int main()
{
	EventSystem::createInstance();
	Game::createInstance();
	{
		if (!GAME->setup(DISPLAY_WIDTH, DISPLAY_HEIGHT))
		{
			std::cout << "Failed to create game instance.\n";
			system("pause");
			return EXIT_FAILURE;
		}
	}
	Game::destroyInstance();

	EventSystem::destroyInstance();

	return 0;
}