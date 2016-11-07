#include "NetClient.h"
#include "Common.h"
#include <sstream>

NetClient* NetClient::sp_instance = NULL;

NetClient::NetClient()
{
	m_isConnected = false;
}

NetClient::~NetClient()
{
	cleanup();
}


bool NetClient::setup()
{
	std::cout << "Starting client.\n";

	if (!RPCManager::createInstance()->setup())
	{
		std::cout << "Failed to create RPC manager instance.\n";
		return false;
	}

	REGISTRY->RegisterCreationFunction<GameObject>();
	REGISTRY->RegisterCreationFunction<Archer>();
	REGISTRY->RegisterCreationFunction<TownCenter>();

	return true;
}

void NetClient::cleanup()
{
	RPCManager::destroyInstance();
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
		{
			printf("The server is full.\n");
		}
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
		case PacketType::REPLICATION_PACKET:
		{
			RakNet::BitStream bsIn(mp_packet->data, mp_packet->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			while (bsIn.GetNumberOfUnreadBits() > 0)
			{
				uint32_t netId, classId;
				bsIn >> netId;
				bsIn >> classId;
				GameObject* tmp = LINKING->getGameObject(netId, true, classId);
				tmp->read(bsIn);
			}
		}
		break;
		case PacketType::RPC_PACKET:
		{
			BitStream iStream(mp_packet->data, mp_packet->length, false);

			BitStream oStream;

			oStream.Write(iStream);

			RPC->processRPC(oStream);
		}
		break;
		case NetMessages::REQUEST_WRITE_PACKET:
		{
			RakNet::BitStream bsIn(mp_packet->data, mp_packet->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			int index;
			bsIn >> index;
			writeStateToFile(index);
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

void NetClient::sendToServer(BitStream& out)
{
	RakNet::SystemAddress addr = mp_peer->GetSystemAddressFromIndex(0);

	mp_peer->Send(&out, HIGH_PRIORITY, UNRELIABLE, 0, addr, false);
}


void NetClient::writeStateToFile(int clientNum)
{
	std::stringstream sstream;
	sstream
		<< "../Assets/data/"
		<< "CurrentState"
		<< clientNum
		<< ".txt";

	std::ofstream of(sstream.str());
	if (!of.fail())
	{
		for (size_t i = 0; i < OBJECT_MANAGER->getNumUnits(); i++)
		{
			OBJECT_MANAGER->getAtIndex(i)->writeToFile(of);
		}
	}
	else
	{
		std::cout << "Failed to open state file.\n";
	}
}