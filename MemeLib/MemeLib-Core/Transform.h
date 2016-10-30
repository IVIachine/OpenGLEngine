#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector3.h"
#include "Matrix.h"

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

	Matrix getModel() const;

	Vec3& getPosition();
	Vec3& getRot();
	Vec3& getScale();

	void setPosition(Vec3 pos);
	void setRot(Vec3 rot);
	void setScale(Vec3 scale);
	

private:
	Vec3 m_pos;
	Vec3 m_scale;
	Vec3 m_rot;
};
#endif
