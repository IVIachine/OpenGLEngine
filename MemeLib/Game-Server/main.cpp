#include "Common.h"

int main()
{
	Maths::seedRandom();
	NetServer::createInstance();

	bool isRunning = SERVER->setup();

	if (!isRunning)
	{
		std::cout << "Failed to create game instance.\n";
		system("pause");
		return EXIT_FAILURE;
	}

	registerRPCs();

	while (isRunning)
	{
		SERVER->update();
	}

	NetServer::destroyInstance();

	return 0;
}