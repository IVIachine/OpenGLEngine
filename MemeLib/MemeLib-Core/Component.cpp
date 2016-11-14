#include "Component.h"

Component::Component(const ComponentID & id)
{
	m_id = id;
}

Component::~Component()
{
}

ComponentID Component::getID() const
{
	return m_id;
}
