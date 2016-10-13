#include "Mouse.h"

Mouse* Mouse::sp_instance = NULL;

Mouse::Mouse()
{
	m_mouseNew = MouseState();
	m_mouseOld = MouseState();
}

Mouse::~Mouse()
{
}


Mouse* Mouse::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void Mouse::destroyInstance()
{
	delete sp_instance;
}

Mouse* Mouse::createInstance()
{
	sp_instance = new Mouse();
	return getInstance();
}


void Mouse::beginStep()
{
	MouseState::beginStep(sp_instance->m_mouseNew);
}

void Mouse::endStep()
{
	sp_instance->m_mouseOld = MouseState(sp_instance->m_mouseNew);
	MouseState::endStep(sp_instance->m_mouseNew);
}


bool Mouse::getButton(Buttons button)
{
	return isNew(button);
}

bool Mouse::getButtonDown(Buttons button)
{
	return isNew(button) && !isOld(button);
}

bool Mouse::getButtonUp(Buttons button)
{
	return !isNew(button) && isOld(button);
}


bool Mouse::isNew(Buttons button)
{
	return m_mouseOld.mStateNew[button];
}

bool Mouse::isOld(Buttons button)
{
	return m_mouseOld.mStateOld[button];
}