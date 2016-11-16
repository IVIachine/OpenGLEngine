#ifndef _NET_H_
#define _NET_H_

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>

#include "LinkingContext.h"
#include "ObjectCreationRegistry.h"
#include "GameObjectManager.h"

typedef RakNet::BitStream		BitStream;
typedef RakNet::RakNetGUID		NetGUID;
typedef RakNet::SystemAddress	NetAddress;

enum PacketType
{
	REPLICATION_PACKET = ID_USER_PACKET_ENUM + 1,
	RPC_PACKET,
	NET_USER_PACKET
};

#endif // !_NET_H_
