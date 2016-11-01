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

const UnitID PLAYER_UNIT_ID = 0;
//const UnitID INVALID_UNIT_ID = UINT_MAX;

#define UNITS UnitManager::getInstance()

class UnitManager: public EventListener
{
public:
	static UnitManager*	getInstance();
	static void			disposeInstance();
	static UnitManager*	createInstance(Uint32 maxSize);

	Unit* createUnit(const Sprite& sprite, NavMesh* graph, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);

	Unit* getUnit(const UnitID& id) const;
	void deleteUnit(const UnitID& id);
	void deleteRandomUnit();
	void deleteAll();
	void drawAll() const;
	void updateAll(float elapsedTime);

	Unit* getPlayerUnit() const { return getUnit(PLAYER_UNIT_ID); };
	virtual void handleEvent(const Event& ev);
	bool setup();
private:
	UnitManager(Uint32 maxSize);
	~UnitManager() {};

	static UnitID msNextUnitID;
	MemoryPool mPool;
	std::map<UnitID, Unit*> mUnitMap;

	static UnitManager* sp_instance;
};

#endif