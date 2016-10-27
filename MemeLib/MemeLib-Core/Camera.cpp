#include "Camera.h"

Camera::Camera(const Vec3 & pos, float fov, float aspect, float zNear, float zFar)
{
	m_fov = fov;
	m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	m_pos = pos;
	m_forward = Vec3(0, 0, 0);
	m_up = Vec3(0, 1, 0);
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

void Camera::setPos(Vec3 pos)
{
	m_pos = pos;
}

Vec3 Camera::getPos()
{
	return m_pos;
}

Vec3 Camera::getFowardVector()
{
	return m_forward;
}

Vec3 Camera::getUpVector()
{
	return m_up;
}

void Camera::setFront(Vec3 front)
{
	m_forward = front;
}

