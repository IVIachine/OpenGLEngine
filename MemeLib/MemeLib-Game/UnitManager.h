#ifndef _UNIT_MANAGER_H_
#define _UNIT_MANAGER_H_

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <MemoryPool.h>
#include <map>
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "Unit.h"
#include <vector>

#define UNITS UnitManager::getInstance()

class Unit;
class Sprite;
struct TransformData;
struct PhysicsData;

const UnitID PLAYER_UNIT_ID = 0;

class UnitManager : public Trackable
{
public:
	static UnitManager*	getInstance();
	static void			disposeInstance();
	static UnitManager*	createInstance(Uint32 maxSize);

	bool	setup();
	void	cleanup();

	Unit*	createUnit(const Sprite& sprite, bool shouldWrap = true, const TransformData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);
	Unit*	createPlayerUnit(const Sprite& sprite, bool shouldWrap = true, const TransformData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA);
	Unit*	createRandomUnit(const Sprite& sprite);


	Unit*	getUnit(const UnitID& id) const;
	void	deleteUnit(const UnitID& id);
	void	deleteRandomUnit();

	void	drawAll() const;
	void	updateAll(float elapsedTime);

	Unit*	getPlayerUnit() const { return getUnit(PLAYER_UNIT_ID); };
	size_t	getUnitCount() { return m_unitMap.size(); }

	std::vector<Unit*> toList();
	std::vector<Unit*> findUnitsInRadius(Vector2 pos, float radius);
	std::vector<Unit*> findUnitsInRadius(std::vector<Unit*>* source, Vector2 pos, float radius);

private:
	UnitManager(Uint32 maxSize);
	~UnitManager();

	static UnitID ms_nextUnitID;
	MemoryPool m_pool;
	std::map<UnitID, Unit*> m_unitMap;

	static UnitManager* sp_instance;
};

#endif