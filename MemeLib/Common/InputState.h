#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <Trackable.h>
#include <BitStream.h>
class InputState: public Trackable
{
public: 
	InputState() :
		mDesiredForwardAmount(0),
		mDesiredBackAmount(0) {};

	float getDesiredVerticalDelta() const { return mDesiredForwardAmount - mDesiredBackAmount; };
	bool write(RakNet::BitStream& stream) const; 
	bool read(RakNet::BitStream& stream);
	void update(float deltaTime);
	bool checkValidState() { return mDesiredBackAmount != 0 || mDesiredForwardAmount != 0; };
private: 
	float mDesiredForwardAmount, mDesiredBackAmount;
};
#endif
