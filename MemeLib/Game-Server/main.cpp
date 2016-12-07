#include "Common.h"
#include "GameTime.h"
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
	RPC->setServer(true);
	registerRPCs();
	while (isRunning)
	{
		TIME->beginStep();
		TIME->step();
		SERVER->update();
		TIME->endStep();
	}

	NetServer::destroyInstance();

	return 0;
}