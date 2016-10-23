#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_

#include <Trackable.h>
#include "Vector2.h"
#include "Component.h"

struct TransformData : public Trackable
{
	TransformData() : position(Vector2::ZERO), angle(0.0f) {};
	TransformData(const Vector2& position, float angle) :
		position(position), angle(angle) {};

	Vector2 position;
	float angle;
};

const TransformData ZERO_POSITION_DATA;

class TransformComponent : public Component
{
public:
	const Vector2& getPosition() const { return m_data.position; };
	void	setPosition(const Vector2& position) { m_data.position = position; wrapCoords(); };
	void	modPosition(const Vector2& mod) { m_data.position += mod; wrapCoords(); };

	float	getRotation() const { return m_data.angle; };
	void	setRotation(float angle) { m_data.angle; };
	void	modFacing(float mod) { m_data.angle += mod; };

	const	TransformData& getData() const { return m_data; };
	void	setData(const TransformData& data) { m_data = data; wrapCoords(); };
	void	modData(const TransformData& data) { m_data.position += data.position; m_data.angle += data.angle; wrapCoords(); };

	Vector2 forward()	const;
	Vector2 backward()	const;
	Vector2 left()		const;
	Vector2 right()		const;

private:
	TransformData m_data;
	bool m_wrap;

	TransformComponent(
		const ComponentID& id, bool shouldWrap = true) :
		Component(id), m_wrap(shouldWrap) {};

	~TransformComponent() {};

	void wrapCoords();

	friend class ComponentManager;
};

#endif