#ifndef MOVE_LIST_H
#define MOVE_LIST_H
#include <Trackable.h>

#include "Move.h"
#include <vector>
#include <algorithm>

class MoveList :public Trackable
{
public:
	MoveList();
	~MoveList();

	const Move& addMove(const InputState& inputState, float timestamp);
	bool sendInputPacket(RakNet::BitStream& inputPacket);
	void pushBackMove(const Move& move);
	void clearList() { mMoves.clear(); };
	std::vector<Move> getData() { return mMoves; };
	size_t getSize() { return mMoves.size(); };
private:
	std::vector<Move> mMoves;
	float mLastMoveTimestamp;
};
#endif
