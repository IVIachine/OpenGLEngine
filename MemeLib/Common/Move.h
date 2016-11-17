#ifndef MOVE_H
#define MOVE_H

#include <Trackable.h>
#include "InputState.h"

class Move 
{
public: 
	Move() {}
	Move(const InputState& inInputState, float inTimestamp, float inDeltaTime) :
		mInputState(inInputState),
		mTimestamp(inTimestamp),
		mDeltaTime(inDeltaTime) {};

	const InputState& GetInputState() const { return mInputState; };
	float GetTimestamp() const { return mTimestamp; };
	float GetDeltaTime() const { return mDeltaTime; };
	bool write(RakNet::BitStream& stream) const; 
	bool read(RakNet::BitStream& stream);
private:
	InputState mInputState; 
	float mTimestamp; 
	float mDeltaTime;
};
#endif
