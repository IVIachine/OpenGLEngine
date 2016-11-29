#include "MoveList.h"
#include "Net.h"
#include "GameTime.h"

MoveList::MoveList()
{
	mLastMoveTimestamp = 0;
}


MoveList::~MoveList()
{
}

const Move & MoveList::addMove(const InputState & inputState, float timestamp)
{
	float deltaTime = mLastMoveTimestamp >= 0.f ? timestamp - mLastMoveTimestamp : 0.f;

	mMoves.emplace_back(inputState, timestamp, deltaTime); 

	mLastMoveTimestamp = timestamp; 

	return mMoves.back();
}

bool MoveList::sendInputPacket(RakNet::BitStream& inputPacket)
{
	if (!mMoves.empty()) 
	{
		inputPacket.Write((RakNet::MessageID)MOVE_REQUEST_PACKET);

		float timeStamp = TIME->getCurrentTime();
		inputPacket.Write(timeStamp);

		//we only want to send the last three moves 
		int moveCount = mMoves.size(); 
		int startIndex = moveCount > 3 ? moveCount - 3 - 1: 0; 
		inputPacket.Write(moveCount - startIndex); //,2; 
		for(int i = startIndex; i < moveCount; i++) 
		{ 
			mMoves[i].write(inputPacket);
		}
		mMoves.clear();
		return true;
	}
	return false;
}

void MoveList::pushBackMove(const Move & move)
{
	mMoves.push_back(move);
}

