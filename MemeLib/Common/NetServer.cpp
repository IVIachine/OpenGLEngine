#include "NetServer.h"
#include "Common.h"
#include "ClientProxy.h"

NetServer* NetServer::sp_instance = NULL;

NetServer::NetServer()
{
}

NetServer::~NetServer()
{
	clear();
}


bool NetServer::setup()
{
	std::cout << "Starting server.\n";

	if (!RPCManager::createInstance()->setup())
	{
		std::cout << "Failed to create RPC manager instance.\n";
		return false;
	}

	GameObjectManager::createInstance();

	REGISTRY->RegisterCreationFunction<GameObject>();
	REGISTRY->RegisterCreationFunction<Paddle>();
	REGISTRY->RegisterCreationFunction<Ball>();

	RakNet::SocketDescriptor socketDesc(SERVER_PORT, 0);
	mp_peer = RakNet::RakPeerInterface::GetInstance();
	mp_peer->Startup(MAX_CLIENTS, &socketDesc, 1);
	mp_peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	
	generateState();

	return true;
}

void NetServer::clear()
{
	GameObjectManager::destroyInstance();

	RPCManager::destroyInstance();
}

void NetServer::handleNewClient(BitStream& iStream, NetAddress addr)
{
	if (mp_packet->data[0] == ID_NEW_INCOMING_CONNECTION)
	{
		size_t		index = m_clients.size();
		std::string name = "Client Name";
		NetGUID		guid = mp_packet->guid;

		if (index == 0)
		{
			PaddleServer* firstPaddle = new PaddleServer();
			firstPaddle->setLoc(Vec3(5, 0, 0));
			uint32_t id = LINKING->getNetworkId(firstPaddle, true); //Also this id

		}
		else if (index == 1)
		{
			PaddleServer* secondPaddle = new PaddleServer();
			secondPaddle->setLoc(Vec3(-5, 0, 0));
			uint32_t id = LINKING->getNetworkId(secondPaddle, true); //This id
		}

		m_clients[addr] = ClientProxy(addr, guid, index, name); //Create and set the target paddle ID to the Paddle Link ID

		std::cout
			<< m_clients[addr].getName() << " has joined the server."
			<< "\n";

		RakNet::BitStream stream;
		stream.Write((RakNet::MessageID)REPLICATION_PACKET);
		for (auto& pair : OBJECT_MANAGER->getData())
		{
			pair.second->sendToServer(stream);
		}
		sendByAddress(mp_packet->systemAddress, stream);

		RakNet::BitStream stream2;
		stream2.Write((RakNet::MessageID)REQUEST_WRITE_PACKET);
		stream2.Write(mp_peer->GetIndexFromSystemAddress(mp_packet->systemAddress));
		sendByAddress(mp_packet->systemAddress, stream2);
	}
	else
	{
		std::cout << "Bad incoming connection from unknown packet\n";
	}
}

void NetServer::update()
{
	for (mp_packet = mp_peer->Receive(); mp_packet; mp_peer->DeallocatePacket(mp_packet), mp_packet = mp_peer->Receive())
	{
		NetAddress addr = mp_packet->systemAddress;

		if (m_clients.find(addr) == m_clients.end())
		{
			BitStream iStream(mp_packet->data, mp_packet->length, false);
			NetAddress addr = mp_packet->systemAddress;
			handleNewClient(iStream, addr);
			continue;
		}

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
		case PacketType::RPC_PACKET:
		{
			BitStream iStream(mp_packet->data, mp_packet->length, false);
			BitStream oStream;
			oStream.Write(iStream);

			for (auto& pair : m_clients)
			{
				sendByAddress(pair.first, oStream);
			}
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


bool NetServer::sendByAddress(NetAddress addr, BitStream& stream)
{
	mp_peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, addr, false, 0U);

	return true;
}

bool NetServer::sendByGuid(NetGUID guid, BitStream& stream)
{
	sendByAddress(mp_peer->GetSystemAddressFromGuid(guid), stream);

	return true;
}

bool NetServer::sendByIndex(size_t index, BitStream& stream)
{
	sendByAddress(mp_peer->GetSystemAddressFromIndex(index), stream);

	return true;
}


void NetServer::generateState()
{
	BallServer* ball = new BallServer();
	ball->setLoc(Vec3(0, 0, 0));
	LINKING->getNetworkId(ball, true);

	std::cout << "State Generated\n";
}