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


glm::mat4 Transform::getModel() const
{
	glm::mat4 posMatrix = glm::translate(m_pos);
	glm::mat4 rotXMatrix = glm::rotate(m_rot.x, Vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(m_rot.y, Vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(m_rot.z, Vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(m_scale);

	glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

	return posMatrix * rotMatrix * scaleMatrix;
}

Vec3& Transform::getPos() { return m_pos; };
Vec3& Transform::getRot() { return m_rot; };
Vec3& Transform::getScale() { return m_scale; };

void Transform::setPos(Vec3 pos) { m_pos = pos; };
void Transform::setRot(Vec3 rot) { m_rot = rot; };
void Transform::setScale(Vec3 scale) { m_scale = scale; };
