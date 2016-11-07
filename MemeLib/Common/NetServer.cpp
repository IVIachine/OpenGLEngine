#include "NetServer.h"
#include "Common.h"

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

	if (!RPCManager::createInstance()->setup())
	{
		std::cout << "Failed to create RPC manager instance.\n";
		return false;
	}

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

void NetServer::cleanup()
{
	RPCManager::destroyInstance();
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
			RakNet::BitStream stream;
			stream.Write((RakNet::MessageID)REPLICATION_PACKET);
			for (size_t i = 0; i < OBJECT_MANAGER->getNumUnits(); i++)
			{
				OBJECT_MANAGER->getAtIndex(i)->sendToServer(stream);
			}
			sendByAddress(mp_packet->systemAddress, stream);

			RakNet::BitStream stream2;
			stream2.Write((RakNet::MessageID)REQUEST_WRITE_PACKET);
			stream2.Write(mp_peer->GetIndexFromSystemAddress(mp_packet->systemAddress));
			sendByAddress(mp_packet->systemAddress, stream2);

			m_numClients++;
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
			
			for (size_t i = 0; i < m_numClients; i++)
			{
				BitStream oStream;
				oStream.Write(iStream);

				sendByIndex(i, oStream);
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


bool NetServer::sendByAddress(SystemAddress addr, BitStream& stream)
{
	mp_peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, addr, false, 0U);

	return true;
}

bool NetServer::sendByGuid(GUId guid, BitStream& stream)
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
	OBJECT_MANAGER->addObject(elfCent1);

	TownCenter* wereCent1 = new TownCenter();
	wereCent1->setHealth(100);
	wereCent1->setLoc(Vec3(20, 40, 10));
	wereCent1->setType(MonsterType::WEREWOLVES);
	OBJECT_MANAGER->addObject(wereCent1);

	TownCenter* vampCent1 = new TownCenter();
	vampCent1->setHealth(100);
	vampCent1->setLoc(Vec3(20, 40, 10));
	vampCent1->setType(MonsterType::VAMPIRES);
	OBJECT_MANAGER->addObject(vampCent1);

	TownCenter* orcCent1 = new TownCenter();
	orcCent1->setHealth(100);
	orcCent1->setLoc(Vec3(20, 40, 10));
	orcCent1->setType(MonsterType::ORCS);
	OBJECT_MANAGER->addObject(orcCent1);

	TownCenter* orcCent2 = new TownCenter();
	orcCent2->setHealth(40);
	orcCent2->setLoc(Vec3(20, 40, 10));
	orcCent2->setType(MonsterType::ORCS);
	OBJECT_MANAGER->addObject(orcCent2);

	Archer* elf1 = new Archer();
	elf1->setCenter(elfCent1);
	elf1->setHealth(100);
	elf1->setAction(CurrentAction::WALKING);
	elf1->setLoc(Vec3(20, 40, 10));
	OBJECT_MANAGER->addObject(elf1);

	Archer* elf2 = new Archer();
	elf2->setCenter(elfCent1);
	elf2->setHealth(100);
	elf2->setAction(CurrentAction::WALKING);
	elf2->setLoc(Vec3(20, 40, 10));
	OBJECT_MANAGER->addObject(elf2);

	Archer* were1 = new Archer();
	were1->setCenter(wereCent1);
	were1->setHealth(100);
	were1->setAction(CurrentAction::WALKING);
	were1->setLoc(Vec3(20, 40, 10));
	OBJECT_MANAGER->addObject(were1);

	Archer* vamp1 = new Archer();
	vamp1->setCenter(vampCent1);
	vamp1->setHealth(100);
	vamp1->setAction(CurrentAction::WALKING);
	vamp1->setLoc(Vec3(20, 40, 10));
	OBJECT_MANAGER->addObject(vamp1);

	Archer* orc1 = new Archer();
	orc1->setCenter(orcCent1);
	orc1->setHealth(100);
	orc1->setAction(CurrentAction::WALKING);
	orc1->setLoc(Vec3(20, 40, 10));
	OBJECT_MANAGER->addObject(orc1);

	Archer* orc2 = new Archer();
	orc2->setCenter(orcCent1);
	orc2->setHealth(100);
	orc2->setAction(CurrentAction::WALKING);
	orc2->setLoc(Vec3(20, 40, 10));
	OBJECT_MANAGER->addObject(orc2);

	Archer* orc3 = new Archer();
	orc3->setCenter(orcCent2);
	orc3->setHealth(100);
	orc3->setAction(CurrentAction::WALKING);
	orc3->setLoc(Vec3(20, 40, 10));
	OBJECT_MANAGER->addObject(orc3);

	std::cout << "State Generated\n";
}