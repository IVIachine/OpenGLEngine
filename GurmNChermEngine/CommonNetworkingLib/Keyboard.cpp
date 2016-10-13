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


Keyboard* Keyboard::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void Keyboard::destroyInstance()
{
	delete sp_instance;
}

Keyboard* Keyboard::createInstance()
{
	sp_instance = new Keyboard();
	return getInstance();
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


bool Keyboard::getKey(Keys key)
{
	return isNew(key);
}

bool Keyboard::getKeyDown(Keys key)
{
	return isNew(key) && !isOld(key);
}

bool Keyboard::getKeyUp(Keys key)
{
	return !isNew(key) && isOld(key);
}


bool Keyboard::isNew(Keys key)
{
	return m_keysOld.mStateNew[key];
}

bool Keyboard::isOld(Keys key)
{
	return m_keysOld.mStateOld[key];
}