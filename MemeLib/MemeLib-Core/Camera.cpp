#include "Camera.h"

Camera::Camera(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar)
{
	m_fov = fov;
	m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	m_pos = pos;
	m_forward = glm::vec3(0, 0, 0);
	m_up = glm::vec3(0, 1, 0);
}

Camera::~Camera()
{
}


glm::mat4 Camera::getViewProjection() const
{
	return m_perspective * glm::lookAt(m_pos, m_pos + m_forward, m_up);
}

glm::mat4 Camera::getPerspective() const
{
	return m_perspective;
}

float Camera::getFOV() const
{
	return m_fov;
}

void Camera::setPos(glm::vec3 pos)
{
	m_pos = pos;
}

glm::vec3 Camera::getPos()
{
	return m_pos;
}

glm::vec3 Camera::getFowardVector()
{
	return m_forward;
}

glm::vec3 Camera::getUpVector()
{
	return m_up;
}

void Camera::setFront(glm::vec3 front)
{
	m_forward = front;
}

