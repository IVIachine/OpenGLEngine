#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "GameObject.h"
#include <limits>

typedef size_t ComponentID;
const ComponentID INVALID_COMPONENT_ID = UINT_MAX;

class Component :public Trackable
{
public:
	Component(const ComponentID& id) :mID(id) {};
	virtual ~Component() {};

	inline ComponentID getID() { return mID; };
private:
	ComponentID mID;
};

#endif