#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtx\transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) 
	{
		m_fov = fov;
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_pos = pos;
		m_forward = glm::vec3(0, 0, 0);
		m_up = glm::vec3(0, 1, 0);
	};

	inline glm::mat4 getViewProjection() const
	{
		return m_perspective * glm::lookAt(m_pos, m_pos + m_forward, m_up);
	};

	inline glm::mat4 getPerspective() const { return m_perspective; };
	inline float getFOV() const {return m_fov;};
	inline void setPos(glm::vec3 pos)
	{ 
		m_pos = pos;

	};
	inline glm::vec3 getPos() { return m_pos; };
	inline glm::vec3 getFowardVector() { return m_forward; };
	inline glm::vec3 getUpVector() { return m_up; };
	inline void setFront(glm::vec3 front) { m_forward = front; };
	~Camera();

private:
	glm::mat4 m_perspective;
	glm::vec3 m_pos;
	glm::vec3 m_forward; //Camera rotations
	glm::vec3 m_up;
	float m_fov;
};
#endif
