#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "GameObject.h"
#include <limits>

typedef size_t ComponentID;
const ComponentID INVALID_COMPONENT_ID = UINT_MAX;

class Component :public Trackable
{
public:
	Component(const ComponentID& id);
	virtual ~Component();

	ComponentID getID() const;

private:
	ComponentID m_id;
};

#endif