#pragma once
#include "Event.h"
#include "Vector3.h"
class ChangeTargetEvent:public Event
{
private:
	Vec3 mTarg;
public:
	ChangeTargetEvent(Vec3 targ);
	~ChangeTargetEvent();

	Vec3 getTarg() const { return mTarg; };
};

