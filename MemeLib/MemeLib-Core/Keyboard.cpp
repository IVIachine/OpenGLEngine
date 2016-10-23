#include "Keyboard.h"

Keyboard* Keyboard::sp_instance = NULL;

Keyboard::Keyboard()
{
	m_keysNew = KeyState();
	m_keysOld = KeyState();
}

Keyboard::~Keyboard()
{
}


void Keyboard::beginStep()
{
	KeyState::beginStep(m_keysNew);
}

void Keyboard::endStep()
{
	m_keysOld = KeyState(m_keysNew);
	KeyState::endStep(m_keysNew);
}


bool Keyboard::getKey(KeyCode key)
{
	return isNew(key);
}

bool Keyboard::getKeyDown(KeyCode key)
{
	return isNew(key) && !isOld(key);
}

bool Keyboard::getKeyUp(KeyCode key)
{
	return !isNew(key) && isOld(key);
}


bool Keyboard::isNew(KeyCode key)
{
	return m_keysOld.mStateNew[key];
}

bool Keyboard::isOld(KeyCode key)
{
	return m_keysOld.mStateOld[key];
}