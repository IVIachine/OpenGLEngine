#include "Camera.h"

Camera::Camera(const Vec3 & pos, float fov, float aspect, float zNear, float zFar)
{
	m_fov = fov;
	m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	m_pos = pos;
	m_forward = Vec3(0, 0, 0);
	m_up = Vec3(0, 1, 0);
	m_near = zNear;
	m_far = zFar;
}

Camera::~Camera()
{
}


Matrix Camera::getViewProjection() const
{
	return m_perspective * glm::lookAt(m_pos, m_pos + m_forward, m_up);
}

Matrix Camera::getPerspective() const
{
	return m_perspective;
}


float Camera::getFOV() const
{
	return m_fov;
}


Vec3 Camera::getPosition() const
{
	return m_pos;
}

Vec3 Camera::getFoward() const
{
	return m_forward;
}

Vec3 Camera::getUp() const
{
	return m_up;
}


void Camera::setForward(Vec3 front)
{
	m_forward = front;
}

void Camera::setPosition(Vec3 pos)
{
	m_pos = pos;
}