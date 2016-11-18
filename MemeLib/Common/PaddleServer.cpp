#include "PaddleServer.h"
#include "ResourceManager.h"
#include "LinkingContext.h"

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
	std::vector<Move> moveList = moves.getData();
	for (size_t i = 0; i < moveList.size(); i++)
	{
		//std::cout << moveList[i].GetInputState().getDesiredVerticalDelta() << std::endl;
		mLoc.y += moveList[i].GetInputState().getDesiredVerticalDelta();
	}
	moves.clearList();
}

void PaddleServer::write(RakNet::BitStream & stream) const
{
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