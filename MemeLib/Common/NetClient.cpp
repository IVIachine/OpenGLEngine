#include "NetClient.h"
#include <iostream>
#include "NetServer.h"

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

	RakNet::SocketDescriptor socketDesc;
	mp_peer = RakNet::RakPeerInterface::GetInstance();
	mp_peer->Startup(1, &socketDesc, 1);

	return true;
}

void NetClient::cleanup()
{
}

void NetClient::update()
{
	if (!m_isConnected)
		return;

	for (mp_packet = mp_peer->Receive(); mp_packet; mp_peer->DeallocatePacket(mp_packet), mp_packet = mp_peer->Receive())
	{
		switch (mp_packet->data[0])
		{
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
		{
			printf("Another client has disconnected.\n");
		}
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
			printf("Message with identifier %i has arrived.\n", mp_packet->data[0]);
			break;
		}
	}
}

void NetClient::connect(const std::string address)
{
	RakNet::SocketDescriptor socketDesc;
	mp_peer = RakNet::RakPeerInterface::GetInstance();
	mp_peer->Startup(1, &socketDesc, 1);

	RakNet::ConnectionAttemptResult res = mp_peer->Connect(address.c_str(), SERVER_PORT, 0, 0);

	m_isConnected = true;
}

bool NetClient::isConnected() const
{
	return m_isConnected;
}