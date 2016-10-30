#include "ChangeTargetEvent.h"



ChangeTargetEvent::ChangeTargetEvent(Vec3 targ)
	:Event(TARGET_EVENT)
{
	mTarg = targ;
}


ChangeTargetEvent::~ChangeTargetEvent()
{
}
