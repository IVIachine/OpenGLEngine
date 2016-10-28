#pragma once

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <MemoryPool.h>
#include <map>
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "Unit.h"

class Unit;
class Sprite;
struct PositionData;
struct PhysicsData;

const UnitID PLAYER_UNIT_ID = 0;

#define UNITS UnitManager::getInstance()

class UnitManager : public Trackable
{
public:
	static UnitManager*	getInstance();
	static void			disposeInstance();
	static UnitManager*	createInstance(Uint32 maxSize);

	Unit* createUnit(const Sprite& sprite, NavigationMesh* graph, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);

	Unit* getUnit(const UnitID& id) const;
	void deleteUnit(const UnitID& id);
	void deleteRandomUnit();

	void drawAll() const;
	void updateAll(float elapsedTime);

	Unit* getPlayerUnit() const { return getUnit(PLAYER_UNIT_ID); };

	bool setup();
private:
	UnitManager(Uint32 maxSize);
	~UnitManager() {};

	static UnitID msNextUnitID;
	MemoryPool mPool;
	std::map<UnitID, Unit*> mUnitMap;

	static UnitManager* sp_instance;
};

