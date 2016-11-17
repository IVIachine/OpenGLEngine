#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <Trackable.h>
#include <BitStream.h>
class InputState: public Trackable
{
public: 
	InputState() :
		mDesiredForwardAmount(0),
		mDesiredBackAmount(0),
		mIsShooting(false) {};

	float getDesiredVerticalDelta() const { return mDesiredForwardAmount - mDesiredBackAmount; };
	bool isShooting() const { return mIsShooting; };
	bool write(RakNet::BitStream& stream) const; 
	bool read(RakNet::BitStream& stream);
	void update(float deltaTime);

private: 
	float mDesiredForwardAmount, mDesiredBackAmount; 
	bool mIsShooting;
};
#endif
