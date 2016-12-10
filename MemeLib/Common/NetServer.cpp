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

	if (!GameTime::createInstance()->setup())
	{
		std::cout << "Failed to create Time instance.\n";
		return false;
	}

	GameObjectManager::createInstance();

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
	GameTime::destroyInstance();
}

void NetServer::handleNewClient(BitStream& iStream, NetAddress addr)
{
	if (mp_packet->data[0] == ID_NEW_INCOMING_CONNECTION)
	{
		size_t		index = m_clients.size();
		std::string name = "Client Name";
		NetGUID		guid = mp_packet->guid;
		uint32_t id = 999;
		if (index == 0)
		{
			m_paddleR = new PaddleServer();
			m_paddleR->setLoc(Vec3(6, 0, 0));
			id = LINKING->getNetworkId(m_paddleR, true); //Also this id

		}
		else if (index == 1)
		{
			m_paddleL = new PaddleServer();
			m_paddleL->setLoc(Vec3(-6, 0, 0));
			id = LINKING->getNetworkId(m_paddleL, true); //This id
		}

		m_clients[addr] = ClientProxy(addr, guid, index, name, id); //Create and set the target paddle ID to the Paddle Link ID

		std::cout
			<< m_clients[addr].getName() << " has joined the server."
			<< "\n";

		for (auto& client : m_clients)
		{
			RakNet::BitStream stream;
			stream.Write((RakNet::MessageID)REPLICATION_PACKET);
			for (auto& pair : OBJECT_MANAGER->getData())
			{
				pair.second->sendToServer(stream);
			}
			sendByAddress(client.second.getAddress(), stream);
		}
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
		case MOVE_REQUEST_PACKET:
		{
			BitStream iStream(mp_packet->data, mp_packet->length, false);
			m_clients.find(addr)->second.readMove(iStream);
		}
		break;
		default:
		{
			printf("Message with identifier %i has arrived.\n", mp_packet->data[0]);
		}
		break;
		}
	}


	if (m_ball && m_paddleL && m_paddleR)
	{
		m_ball->update();

		float ballX = m_ball->getLoc().x;
		float ballY = m_ball->getLoc().y;

		float dyL = glm::distance(m_ball->getLoc(), m_paddleL->getLoc());
		float dyR = glm::distance(m_ball->getLoc(), m_paddleR->getLoc());

		bool rhsPoint = ballX > m_paddleR->getLoc().x;
		bool lhsPoint = ballX < m_paddleL->getLoc().x;
		bool hitPaddle = (lhsPoint && dyL < 1.0f || rhsPoint && dyR < 1.0f);

		float ceil = MAX_PADDLE_Y;
		bool hitCeil = ballY <= -ceil || ballY >= ceil;

		if (hitPaddle)
		{
			m_ball->bounce();
		}
		else if (hitCeil)
		{
			m_ball->flip();
		}
		else if (rhsPoint || lhsPoint)
		{
			if (rhsPoint)
			{
				m_pointsR++;

				std::cout << "Right Scored!\n";
			}
			else if (lhsPoint)
			{
				m_pointsL++;

				std::cout << "Left Scored!\n";
			}

			m_ball->setLoc({ 0, 0, 0 });

			// Send RPC containing score
			std::stringstream sstream;
			sstream << "Score:" << " L: " << m_pointsL << " R: " << m_pointsR << "\n";			
			BitStream oStream;
			oStream.Write((RakNet::MessageID)RPC_PACKET);
			oStream.Write(PING_ID);
			oStream.Write(sstream.str().c_str());
			for (auto& client : m_clients)
			{
				sendByAddress(client.second.getAddress(), oStream);
			}
		}

		if (m_frameCounter >= 10.f)
		{
			RakNet::BitStream stream;
			stream.Write((RakNet::MessageID)REPLICATION_PACKET);
			m_ball->sendToServer(stream);
			
			for (auto& client : m_clients)
			{
				sendByAddress(client.second.getAddress(), stream);
			}

			m_frameCounter = 0;
		}
		else
		{
			m_frameCounter+= TIME->deltaTime();
		}

		for (auto& client : m_clients)
		{
			client.second.update();
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
	m_ball = new BallServer();
	m_ball->setLoc(Vec3(0, 0, 0));
	LINKING->getNetworkId(m_ball, true);

	std::cout << "State Generated\n";
}

void NetServer::broadcastNewLocation(PaddleServer* key)
{
	RakNet::BitStream stream;
	stream.Write((RakNet::MessageID)REPLICATION_PACKET);
	key->sendToServer(stream);
	for (auto& client : m_clients)
	{
		sendByAddress(client.second.getAddress(), stream);
	}
}