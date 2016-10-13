#include "NetServer.h"
#include "Game.h"
#include "UnitManager.h"
#include "EventSystem.h"
#include "ChatEvent.h"
#include <string>

NetServer* NetServer::sp_instance = NULL;

NetServer::NetServer()
{
	
}

NetServer::~NetServer()
{
	RakNet::RakPeerInterface::DestroyInstance(m_peer);
}


void NetServer::setup()
{
	EVENT_SYSTEM->addListener(EV_CHAT_MESSAGE, this);

	RakNet::SocketDescriptor socketDesc(SERVER_PORT, 0);
	m_peer = RakNet::RakPeerInterface::GetInstance();
	m_peer->Startup(MAX_CLIENTS, &socketDesc, 1);
	m_peer->SetMaximumIncomingConnections(MAX_CLIENTS);

	m_numClients = 0;
	m_isRunning = false;
}

void NetServer::update()
{
	for (m_packet = m_peer->Receive(); m_packet; m_peer->DeallocatePacket(m_packet), m_packet = m_peer->Receive())
	{
		switch (m_packet->data[0])
		{
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
		{
			printf("Another client has disconnected.\n");
		}
		break;
		case ID_REMOTE_CONNECTION_LOST:
		{
			m_numClients--;
			printf("Another client has lost the connection.\n");
		}
		break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
		{
			printf("Another client has connected.\n");
		}
		break;
		case ID_NEW_INCOMING_CONNECTION:
		{
			printf("A connection is incoming.\n");
			RakNet::BitStream bsOut;
		}
		break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
		{
			printf("The server is full.\n");
		}
		break;
		case ID_DISCONNECTION_NOTIFICATION:
		{
			
		}
		break;
		case ID_CONNECTION_LOST:
		{

		}
		break;
		case ID_GAME_MESSAGE_1:
		{
		}
		break;
		case NEW_CLIENT_NAME:
		{
			m_numClients++;
			RakNet::RakString rs;
			RakNet::BitStream bsIn(m_packet->data, m_packet->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(rs);
			
			broadcastMessage(rs.C_String());
		}
		break;
		case SERVER_RECIEVE_MESSAGE:
		{
			RakNet::RakString rs;
			RakNet::BitStream bsIn(m_packet->data, m_packet->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(rs);

			std::string chatString = rs.C_String();

			broadcastMessage(chatString);

			//int index = m_peer->GetIndexFromSystemAddress(m_packet->systemAddress);
		}
		break;
		default:
		{
			printf("Unknown message with identifier %i has arrived.\n", m_packet->data[0]);
		}
		break;
		}
	}
}

void NetServer::handleEvent(const Event& ev)
{
	
}


bool NetServer::isRunning() const
{
	return m_isRunning;
}

void NetServer::start()
{
	m_isRunning = true;

	std::cout << "Starting the server\n";
}

void NetServer::stop()
{
	m_isRunning = false;

	std::cout << "Stopping the server\n";
}


void NetServer::sendMessage(std::string message, size_t clientID)
{
	std::cout << message;

	RakNet::BitStream outStream;	
	outStream.Write((RakNet::MessageID)CLIENT_RECIEVE_MESSAGE);
	outStream.Write(message.c_str());
	m_peer->Send(
		&outStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_peer->GetSystemAddressFromIndex(clientID), false);
}

void NetServer::broadcastMessage(std::string message)
{
	for (size_t c = 0; c < m_numClients; c++)
	{
		sendMessage(message, c);
	}
}