#include "PaddleServer.h"
#include "ResourceManager.h"
#include "LinkingContext.h"
#include "NetServer.h"
#include <Timer.h>

PaddleServer::PaddleServer()
{
}


PaddleServer::~PaddleServer()
{
}

void PaddleServer::draw()
{
}

void PaddleServer::updatePaddle(MoveList& moves)
{
	Timer timer;

	bool hasChanged = false;
	std::vector<Move> moveList = moves.getData();
	for (size_t i = 0; i < moveList.size(); i++)
	{
		hasChanged = true;
		mLoc.y += moveList[i].GetInputState().getDesiredVerticalDelta();

		timer.sleepUntilElapsed(moveList[i].GetDeltaTime());
	}
	moves.clearList();

	if (hasChanged)
	{
		SERVER->broadcastNewLocation(this);
	}
}

void PaddleServer::write(RakNet::BitStream & stream) 
{
	if (mLoc.y < MIN_PADDLE_Y)
	{
		mLoc.y = MIN_PADDLE_Y;
	}

	if (mLoc.y > MAX_PADDLE_Y)
	{
		mLoc.y = MAX_PADDLE_Y;
	}

	stream.Write(mLoc.x);
	stream.Write(mLoc.y);
	stream.Write(mLoc.z);
}

void PaddleServer::sendToServer(RakNet::BitStream & stream)
{
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
}

void PaddleServer::sendToServer(RakNet::RakPeerInterface * peer)
{
	RakNet::BitStream stream;
	stream.Write((RakNet::MessageID)REPLICATION_PACKET);
	stream.Write(LINKING->getNetworkId(this, true));
	stream.Write(mClassId);
	write(stream);
	peer->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, peer->GetSystemAddressFromIndex(0), false);
}

void PaddleServer::read(RakNet::BitStream & stream)
{
	stream.Read(mLoc.x);
	stream.Read(mLoc.y);
	stream.Read(mLoc.z);
	setLoc(mLoc);
}

void PaddleServer::writeToFile(std::ofstream & of)
{

}