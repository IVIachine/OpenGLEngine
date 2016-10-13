#include "UnitManager.h"
#include "EventSystem.h"
#include "Event.h"

UnitManager* UnitManager::sp_instance = NULL;


UnitManager::UnitManager()
{
	m_isUpdating = true;
}

UnitManager::~UnitManager()
{
	cleanup();
}


UnitManager* UnitManager::getInstance()
{
	assert(sp_instance != NULL);
	return sp_instance;
}

void UnitManager::destroyInstance()
{
	delete sp_instance;
	sp_instance = NULL;
}

UnitManager* UnitManager::createInstance()
{
	sp_instance = new UnitManager();
	return getInstance();
}


void UnitManager::cleanup()
{
	while (!m_unitList.empty())
	{
		delete m_unitList.back();

		m_unitList.pop_back();
	}
}


Unit* UnitManager::createUnit(Texture2D& texture2D, int speed, Vector2 pos, Vector2 size, Vector2 scale)
{
	Animation anim;
	anim.addSprite(&texture2D, 0, 0, size, speed, pos, scale);

	Unit* unit = NULL;
	unit = new Unit(anim, pos, size, scale);

	m_unitList.push_back(unit);
	
	return unit;
}

Unit* UnitManager::findByIndex(int index)
{
	return m_unitList[index];
}

void UnitManager::removeByIndex(int index)
{
	delete m_unitList[index];
	m_unitList.erase(m_unitList.begin() + index);
}


int UnitManager::count()
{
	return m_unitList.size();
}


bool UnitManager::getPause()
{
	return m_isUpdating;
}

void UnitManager::setPause(bool thePause)
{
	m_isUpdating = thePause;
}


void UnitManager::update()
{
	if (m_isUpdating)
	{
		for (size_t i = 0; i < m_unitList.size(); i++)
		{
			m_unitList[i]->update();
		}
	}
}

void UnitManager::draw()
{
	for (size_t i = 0; i < m_unitList.size(); i++)
	{
		m_unitList[i]->draw();
	}
}