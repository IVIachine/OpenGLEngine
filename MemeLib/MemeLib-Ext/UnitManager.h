#ifndef _UNIT_MANAGER_H_
#define _UNIT_MANAGER_H_

#include <Trackable.h>

#include <MemoryPool.h>
#include <map>
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "Unit.h"
#include "EventListener.h"

class Unit;
class Sprite;
struct PositionData;
struct PhysicsData;

const GameObjectID PLAYER_UNIT_ID = 0;
//const GameObjectID INVALID_GOBJ_ID = UINT_MAX;

#define UNITS UnitManager::getInstance()

class UnitManager: public EventListener
{
public:
	static UnitManager*	getInstance()
	{
		assert(sp_instance != NULL);
		return sp_instance;
	};
	static void			disposeInstance()
	{
		delete sp_instance;
		sp_instance = NULL;
	};
	static UnitManager*	createInstance(size_t maxSize)
	{
		sp_instance = new UnitManager(maxSize);
		return getInstance();
	};

	Unit* createUnit(
		const Sprite& sprite, 
		NavMesh* graph, 
		bool shouldWrap = true, 
		const PositionData& posData = ZERO_POSITION_DATA, 
		const PhysicsData& physicsData = ZERO_PHYSICS_DATA);

	Unit* getUnit(const GameObjectID& id) const;
	bool deleteUnit(const GameObjectID& id);
	void deleteRandomUnit();
	void deleteAll();

	Unit* getPlayerUnit() const { return getUnit(PLAYER_UNIT_ID); };
	virtual void handleEvent(const Event& ev);
	bool setup();

private:
	UnitManager(size_t maxSize);
	~UnitManager() {};

	//static GameObjectID msNextUnitID;
	//MemoryPool mPool;
	std::map<GameObjectID, Unit*> mUnitMap;

	static UnitManager* sp_instance;
};

#endif