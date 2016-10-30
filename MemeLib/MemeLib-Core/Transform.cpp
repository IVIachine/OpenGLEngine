#include "Transform.h"

Transform::Transform()
{
}

Transform::Transform(const Vec3 & pos, const Vec3 & rot, const Vec3 & scale)
	: m_pos(pos), m_rot(rot), m_scale(scale)
{
}

Transform::Transform(const Transform & copy)
{
	m_pos = copy.m_pos;
	m_scale = copy.m_scale;
	m_rot = copy.m_rot;
}

Transform::~Transform()
{
}


Matrix Transform::getModel() const
{
	Matrix posMatrix = glm::translate(m_pos);
	Matrix rotXMatrix = glm::rotate(m_rot.x, Vec3(1, 0, 0));
	Matrix rotYMatrix = glm::rotate(m_rot.y, Vec3(0, 1, 0));
	Matrix rotZMatrix = glm::rotate(m_rot.z, Vec3(0, 0, 1));
	Matrix scaleMatrix = glm::scale(m_scale);

	Matrix rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

	return posMatrix * rotMatrix * scaleMatrix;
}

Vec3& Transform::getPosition() { return m_pos; };
Vec3& Transform::getRot() { return m_rot; };
Vec3& Transform::getScale() { return m_scale; };

void Transform::setPosition(Vec3 pos) { m_pos = pos; };
void Transform::setRot(Vec3 rot) { m_rot = rot; };
void Transform::setScale(Vec3 scale) { m_scale = scale; };
