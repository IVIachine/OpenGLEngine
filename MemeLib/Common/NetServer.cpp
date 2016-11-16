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
	REGISTRY->RegisterCreationFunction<Archer>();
	REGISTRY->RegisterCreationFunction<TownCenter>();

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
		m_clients[addr] = ClientProxy(addr, guid, index, name);

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
	printf("A connection is incoming.\n");

	TownCenter* elfCent1 = new TownCenter();
	elfCent1->setHealth(100);
	elfCent1->setLoc(Vec3(20, 40, 10));
	elfCent1->setType(MonsterType::ELVES);
	LINKING->getNetworkId(elfCent1, true);

	TownCenter* wereCent1 = new TownCenter();
	wereCent1->setHealth(100);
	wereCent1->setLoc(Vec3(20, 40, 10));
	wereCent1->setType(MonsterType::WEREWOLVES);
	LINKING->getNetworkId(wereCent1, true);

	TownCenter* vampCent1 = new TownCenter();
	vampCent1->setHealth(100);
	vampCent1->setLoc(Vec3(20, 40, 10));
	vampCent1->setType(MonsterType::VAMPIRES);
	LINKING->getNetworkId(vampCent1, true);

	TownCenter* orcCent1 = new TownCenter();
	orcCent1->setHealth(100);
	orcCent1->setLoc(Vec3(20, 40, 10));
	orcCent1->setType(MonsterType::ORCS);
	LINKING->getNetworkId(orcCent1, true);

	TownCenter* orcCent2 = new TownCenter();
	orcCent2->setHealth(40);
	orcCent2->setLoc(Vec3(20, 40, 10));
	orcCent2->setType(MonsterType::ORCS);
	LINKING->getNetworkId(orcCent2, true);

	Archer* elf1 = new Archer();
	elf1->setCenter(elfCent1);
	elf1->setHealth(100);
	elf1->setAction(CurrentAction::WALKING);
	elf1->setLoc(Vec3(20, 40, 10));
	LINKING->getNetworkId(elf1, true);

	Archer* elf2 = new Archer();
	elf2->setCenter(elfCent1);
	elf2->setHealth(100);
	elf2->setAction(CurrentAction::WALKING);
	elf2->setLoc(Vec3(20, 40, 10));
	LINKING->getNetworkId(elf2, true);

	Archer* were1 = new Archer();
	were1->setCenter(wereCent1);
	were1->setHealth(100);
	were1->setAction(CurrentAction::WALKING);
	were1->setLoc(Vec3(20, 40, 10));
	LINKING->getNetworkId(were1, true);

	Archer* vamp1 = new Archer();
	vamp1->setCenter(vampCent1);
	vamp1->setHealth(100);
	vamp1->setAction(CurrentAction::WALKING);
	vamp1->setLoc(Vec3(20, 40, 10));
	LINKING->getNetworkId(vamp1, true);

	Archer* orc1 = new Archer();
	orc1->setCenter(orcCent1);
	orc1->setHealth(100);
	orc1->setAction(CurrentAction::WALKING);
	orc1->setLoc(Vec3(20, 40, 10));
	LINKING->getNetworkId(orc1, true);

	Archer* orc2 = new Archer();
	orc2->setCenter(orcCent1);
	orc2->setHealth(100);
	orc2->setAction(CurrentAction::WALKING);
	orc2->setLoc(Vec3(20, 40, 10));
	LINKING->getNetworkId(orc2, true);

	Archer* orc3 = new Archer();
	orc3->setCenter(orcCent2);
	orc3->setHealth(100);
	orc3->setAction(CurrentAction::WALKING);
	orc3->setLoc(Vec3(20, 40, 10));
	LINKING->getNetworkId(orc3, true);

	std::cout << "State Generated\n";
}