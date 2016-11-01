#include "NetClient.h"
#include <iostream>

NetClient* NetClient::sp_instance = NULL;

NetClient::NetClient()
{
}

NetClient::~NetClient()
{
	cleanup();
}


bool NetClient::setup()
{
	std::cout << "Starting client.\n";

	return true;
}

void NetClient::cleanup()
{
}

void NetClient::update()
{
}