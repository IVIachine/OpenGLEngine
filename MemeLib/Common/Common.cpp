#include "Common.h"

void registerRPCs()
{
	RPC->registerUnwrapFunction(PING_ID, readMessage);
}

void readMessage(BitStream& iStream)
{
	RakNet::RakString rakStr;

	iStream.Read(rakStr);

	const char* text = rakStr.C_String();

	MessageRPCStruct pingStruct(text);

	printMessage(pingStruct);
}

void sendMessage(const MessageRPCStruct& message)
{
	BitStream oStream;

	oStream.Write((RakNet::MessageID)RPC_PACKET);

	oStream.Write(PING_ID);

	oStream.Write(message.text);

	CLIENT->sendToServer(oStream);
}

void printMessage(const MessageRPCStruct& message)
{
	std::cout << message.text << "\n";
}
