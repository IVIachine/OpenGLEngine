#ifndef _COMMON_H_
#define _COMMON_H_

#include "Game.h"
#include "Input.h"
#include "EventSystem.h"
#include "NetServer.h"
#include "NetClient.h"

void registerRPCs();


const RPC_ID PING_ID = 'MSG';
struct MessageRPCStruct : public Trackable
{
	const char* text;

	MessageRPCStruct(const char* text = "") : text(text) {};
};

void readMessage(BitStream& iStream);
void sendMessage(const MessageRPCStruct& pingStruct);
void printMessage(const MessageRPCStruct& pingStruct);

#endif // !_COMMON_H_
