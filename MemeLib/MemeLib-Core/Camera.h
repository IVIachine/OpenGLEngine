#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <Trackable.h>

class Camera : public Trackable
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	~Camera();

	glm::mat4	getViewProjection() const;
	glm::mat4	getPerspective() const;

	float		getFOV() const;
	void		setPos(glm::vec3 pos);

	glm::vec3	getPos();
	glm::vec3	getFowardVector();
	glm::vec3	getUpVector();
	void		setFront(glm::vec3 front);	

private:
	glm::mat4	m_perspective;
	glm::vec3	m_pos;
	glm::vec3	m_forward; //Camera rotations
	glm::vec3	m_up;
	float		m_fov;
};
#endif
