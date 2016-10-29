#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector3.h"
#include <gtx\transform.hpp>

class Transform : public Trackable
{
public:
	Transform();
	Transform(
		const Vec3& pos, 
		const Vec3& rot, 
		const Vec3& scale = Vec3(1.0, 1.0, 1.0));
	Transform(const Transform& copy);
	~Transform();

	glm::mat4 getModel() const;

	Vec3& getPos();
	Vec3& getRot();
	Vec3& getScale();

	void setPos(Vec3 pos);
	void setRot(Vec3 rot);
	void setScale(Vec3 scale);
	

private:
	Vec3 m_pos;
	Vec3 m_scale;
	Vec3 m_rot;
};
#endif
