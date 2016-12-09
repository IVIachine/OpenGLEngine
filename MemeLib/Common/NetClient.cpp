#include "NetClient.h"
#include "Common.h"
#include <sstream>
#include "Timer.h"

NetClient* NetClient::sp_instance = NULL;

NetClient::NetClient()
{
	m_Registry = new ObjectCreationRegistry();
	m_Registry->RegisterCreationFunction<GameObject>();
	m_Registry->RegisterCreationFunction<Paddle>();
	m_Registry->RegisterCreationFunction<Ball>();
	m_isConnected = false;
	mIsSimulating = false;
	mSimulationTime = 0;
	m_frameCount = 0;
	mSimulationTimer = new Timer();
}

NetClient::~NetClient()
{
	clear();
}


bool NetClient::setup()
{
	std::cout << "Starting client.\n";

	if (!RPCManager::createInstance()->setup())
	{
		std::cout << "Failed to create RPC manager instance.\n";
		return false;
	}

	m_moves = new MoveList();
	return true;
}

void NetClient::clear()
{
	delete m_moves;
	m_moves = NULL;

	delete m_Registry;
	m_Registry = NULL;

	delete mSimulationTimer;
	mSimulationTimer = NULL;
	RPCManager::destroyInstance();
}


void NetClient::update()
{
	if (!m_isConnected)
		return;

	InputState currentState;
	currentState.update(TIME->deltaTime());
	if (currentState.checkValidState())
	{
		m_moves->addMove(currentState, TIME->getCurrentTime());
	}
	if (m_frameCount >= 2.f) //May need to fix
	{
		RakNet::BitStream stream;

		if (m_moves->sendInputPacket(stream))
		{
			sendToServer(stream);
		}
		m_frameCount = 0;
	}
	else
	{
		m_frameCount += TIME->deltaTime();
	}

	if (mIsSimulating)
	{
		if (mSimulationTimer->getElapsedTime() >= mSimulationTime)
		{
			mSimulationTimer->stop();
			mSimulationTime = 0;
			mIsSimulating = false;
		}
		else
		{
			for (auto paddle : OBJECT_MANAGER->findObjectsOfType<PaddleClient>())
			{
				paddle->updateClient();
			}
		}
	}

	for (auto ball : OBJECT_MANAGER->findObjectsOfType<BallClient>())
	{
		ball->update(10);
	}


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
			//system("cls");
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
				GameObject* tmp = LINKING->getGameObject(netId, true, classId, m_Registry);
				tmp->read(bsIn);
			}
		}
		break;
		case PacketType::RPC_PACKET:
		{
			BitStream iStream(mp_packet->data, mp_packet->length, false);

			BitStream oStream;

			oStream.Write(iStream);

			RPC->process(oStream);
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
		case NetMessages::TIME_PACKET:
		{
			RakNet::BitStream bsIn(mp_packet->data, mp_packet->length, false);

			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

			float timeStamp;

			bsIn >> timeStamp;

			float rtt = TIME->getCurrentTime() - timeStamp;
			mSimulationTime = rtt/2;
			//std::cout << mSimulationTime << std::endl;
			mIsSimulating = true;
			mSimulationTimer->stop();
			mSimulationTimer->start();
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
		for (auto& pair : OBJECT_MANAGER->getData())
		{
			pair.second->writeToFile(of);
		}
	}
	else
	{
		std::cout << "Failed to open state file.\n";
	}
}