#include "NetClient.h"
#include "Game.h"
#include "UnitManager.h"
#include "EventSystem.h"
#include "ChatEvent.h"
#include <string>

NetClient* NetClient::sp_instance = NULL;

NetClient::NetClient()
{
	m_address = LOCAL_HOST;
}

NetClient::~NetClient()
{
	RakNet::RakPeerInterface::DestroyInstance(m_peer);
}


void NetClient::setup()
{
	EVENT_SYSTEM->addListener(EV_CHAT_MESSAGE, this);

	RakNet::SocketDescriptor socketDesc;
	m_peer = RakNet::RakPeerInterface::GetInstance();
	m_peer->Startup(1, &socketDesc, 1);
	
	std::cout 
		<< "Starting the client." 
		<< "\n";

	m_peer->Connect(m_address.c_str(), SERVER_PORT, 0, 0);
}

void NetClient::update()
{
	for (m_packet = m_peer->Receive(); m_packet; m_peer->DeallocatePacket(m_packet), m_packet = m_peer->Receive())
	{
		switch (m_packet->data[0])
		{
		case ID_CONNECTION_REQUEST_ACCEPTED:
		{
			std::cout 
				<< "Our connection request has been accepted."
				<< "\n";
			
			RakNet::BitStream outStream;
			outStream.Write((RakNet::MessageID)NEW_CLIENT_NAME);
			
			std::string str = "$ " + m_user.getName() + " has connected to the chat room.\n";
			outStream.Write(str.c_str());
			
			m_peer->Send(&outStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, getConnectedSystem(0), false);
		}
		break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
		{
			std::cout 
				<< "The server is full."
				<< "\n";
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
		case CLIENT_RECIEVE_MESSAGE:
		{
			RakNet::RakString rakStr;
			RakNet::BitStream inStream(m_packet->data, m_packet->length, false);
			inStream.IgnoreBytes(sizeof(RakNet::MessageID));
			inStream.Read(rakStr);

			ChatMessage chatMessage(rakStr.C_String(), MessageDest::Client);

			EVENT_SYSTEM->fireEvent(ChatEvent(chatMessage));
		}
		break;
		default:
		{
		}
		break;
		}
	}
}

void NetClient::handleEvent(const Event& ev)
{
	if (ev.getType() == EV_CHAT_MESSAGE)
	{
		// get the chat message string
		const ChatEvent& chatEvent = static_cast<const ChatEvent&>(ev);

		ChatMessage chatMessage = chatEvent.getMessage();

		if (chatMessage.getDest() == MessageDest::Server)
		{
			sendMessageToServer(chatMessage);
		}
	}
}


RakNet::SystemAddress NetClient::getConnectedSystem(int index)
{
	if (m_peer == NULL)
	{
		return RakNet::SystemAddress();
	}

	return m_peer->GetSystemAddressFromIndex(index);
}

void NetClient::setAddress(std::string theAddress)
{
	m_address = theAddress;
}


void NetClient::sendMessageToServer(const ChatMessage& message)
{
	GameMessages dest;

	if (message.getDest() == MessageDest::Client)
	{
		// Message is sent from server to client
		dest = CLIENT_RECIEVE_MESSAGE;
	}
	else
	{
		// Message is sent from client to server
		dest = SERVER_RECIEVE_MESSAGE;
	}

	sendMessageToServer(message.getString().c_str(), dest);
}

void NetClient::sendMessageToServer(const char* cstr, GameMessages messageID)
{
	RakNet::BitStream outStream;

	outStream.Write((RakNet::MessageID)messageID);

	outStream.Write(cstr);

	m_peer->Send(&outStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, getConnectedSystem(0), false);
}