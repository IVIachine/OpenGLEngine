
#ifndef _CHANGE_TARGET_EVENT_H_
#define _CHANGE_TARGET_EVENT_H_

#include "Event.h"
#include "Vector3.h"
class ChangeTargetEvent :public Event
{
private:
	Vec3 mTarg;
public:
	ChangeTargetEvent(Vec3 targ);
	~ChangeTargetEvent();

	Vec3 getTarg() const { return mTarg; };
};

#endif // !_CHANGE_TARGET_EVENT_H_