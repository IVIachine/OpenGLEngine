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
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
	{
		switch (packet->data[0])
		{
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			printf("Another client has disconnected.\n");
			break;
		case ID_REMOTE_CONNECTION_LOST:
		{
			printf("Another client has lost the connection.\n");
		}
		break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
		{
			printf("Another client has connected.\n");
		}
		break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
		{
			system("cls");
			printf("Our connection request has been accepted.\n");
		}
		break;
		case ID_NEW_INCOMING_CONNECTION:
		{
			printf("A connection is incoming.\n");
		}
		break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			printf("The server is full.\n");
			break;
		case ID_DISCONNECTION_NOTIFICATION:
		{
				printf("We have been disconnected.\n");
		}
			break;
		case ID_CONNECTION_LOST:
		{
				printf("Connection lost.\n");
		}
			break;
		default:
			printf("Message with identifier %i has arrived.\n", packet->data[0]);
			break;
		}
	}
}