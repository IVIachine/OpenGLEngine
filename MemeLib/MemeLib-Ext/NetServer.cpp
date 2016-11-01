#include "NetServer.h"
#include <iostream>

NetServer* NetServer::sp_instance = NULL;

NetServer::NetServer()
{
}

NetServer::~NetServer()
{
	cleanup();
}

bool NetServer::setup()
{
	std::cout << "Starting server.\n";

	return true;
}

void NetServer::cleanup()
{
}

void NetServer::update()
{
}