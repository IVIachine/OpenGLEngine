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
		m_pos.y += moveList[i].GetInputState().getDesiredVerticalDelta();

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
	if (m_pos.y < MIN_PADDLE_Y)
	{
		m_pos.y = MIN_PADDLE_Y;
	}

	if (m_pos.y > MAX_PADDLE_Y)
	{
		m_pos.y = MAX_PADDLE_Y;
	}

	stream.Write(m_pos.x);
	stream.Write(m_pos.y);
	stream.Write(m_pos.z);
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
	stream.Read(m_pos.x);
	stream.Read(m_pos.y);
	stream.Read(m_pos.z);
	setLoc(m_pos);
}

void PaddleServer::writeToFile(std::ofstream & of)
{

}