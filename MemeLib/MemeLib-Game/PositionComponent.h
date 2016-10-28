#pragma once

#include <Trackable.h>
#include "Vector3.h"
#include "Component.h"

struct PositionData :public Trackable
{
	PositionData() :pos(Vec3(0,0,0)), facing(0.0f) {};
	PositionData(const Vec3& thePos, float theFacing) :pos(thePos), facing(theFacing) {};

	Vec3 pos;
	float facing;
};

const PositionData ZERO_POSITION_DATA;

class PositionComponent :public Component
{
public:
	//getters and setters
	const Vec3& getPosition() const { return mData.pos; };
	void setPosition(const Vec3& pos) { mData.pos = pos; };
	void modPosition(const Vec3& mod) { mData.pos += mod; };
	float getFacing() const { return mData.facing; };
	void setFacing(float facing) { mData.facing; };
	void modFacing(float mod) { mData.facing += mod; };
	const PositionData& getData() const { return mData; };
	void setData(const PositionData& data) { mData = data; };
	void modData(const PositionData& data) { mData.pos += data.pos; mData.facing += data.facing; };

private:
	PositionData mData;

	PositionComponent(const ComponentID& id, bool shouldWrap = true) :Component(id) {};
	~PositionComponent() {};

	friend class ComponentManager;
};