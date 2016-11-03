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
	ObjectCreationRegistry::createInstance();
	LinkingContext::createInstance();
	REGISTRY->RegisterCreationFunction<GameObject>();
	REGISTRY->RegisterCreationFunction<Archer>();
	REGISTRY->RegisterCreationFunction<TownCenter>();
	RakNet::SocketDescriptor socketDesc(SERVER_PORT, 0);
	mp_peer = RakNet::RakPeerInterface::GetInstance();
	mp_peer->Startup(MAX_CLIENTS, &socketDesc, 1);
	mp_peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	mManager = new GameObjectManager();
	return true;
}

void NetServer::cleanup()
{
	LINKING->destroyInstance();
	REGISTRY->destroyInstance();
	delete mManager;
	mManager = NULL;
}

void NetServer::update()
{
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
			TownCenter* cent = new TownCenter();
			cent->setHealth(200);
			cent->setLoc(Vec3(20, 40, 10));
			cent->setType(MonsterType::ELVES);
			cent->send(mp_peer);

			Archer* arch = new Archer();
			arch->setCenter(cent);
			arch->setHealth(100);
			arch->setAction(CurrentAction::WALKING);
			arch->send(mp_peer);

		}
		break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
		{
			printf("The server is full.\n");
		}
		break;
		case ID_DISCONNECTION_NOTIFICATION:
		{
			printf("A client has disconnected.\n");
		}
		break;
		case ID_CONNECTION_LOST:
		{
			printf("A client lost the connection.\n");
		}
		break;
		default:
		{
			printf("Message with identifier %i has arrived.\n", mp_packet->data[0]);
		}
		break;
		}
	}
}