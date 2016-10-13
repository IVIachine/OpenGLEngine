#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <string>
#include <cassert>

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"

#include "EventListener.h"
#include "UserDatabase.h"

#define MAX_CLIENTS 10
#define SERVER_PORT 60000

enum GameMessages
{
	ID_GAME_MESSAGE_1 = ID_USER_PACKET_ENUM + 1,
	NEW_CLIENT_NAME = ID_USER_PACKET_ENUM + 2,
	SERVER_RECIEVE_MESSAGE = ID_USER_PACKET_ENUM + 3,
	CLIENT_RECIEVE_MESSAGE = ID_USER_PACKET_ENUM + 4,
};

const static char* LOCAL_HOST = "127.0.0.1";

#endif // !_NETWORK_H_
