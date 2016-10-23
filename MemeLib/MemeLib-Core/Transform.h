#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>
#include <gtx\transform.hpp>

class Transform
{
public:
	Transform();
	Transform(
		const glm::vec3& pos, 
		const glm::vec3& rot, 
		const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0));
	Transform(const Transform& copy);
	~Transform();

	glm::mat4 getModel() const;

	glm::vec3& getPos();
	glm::vec3& getRot();
	glm::vec3& getScale();

	void setPos(glm::vec3 pos);
	void setRot(glm::vec3 rot);
	void setScale(glm::vec3 scale);
	

private:
	glm::vec3 m_pos;
	glm::vec3 m_scale;
	glm::vec3 m_rot;
};
#endif
