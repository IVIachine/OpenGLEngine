#include "Camera.h"
#include "Graphics.h"

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


Matrix Camera::getViewMatrix() const
{
	return m_perspective * glm::lookAt(m_pos, m_pos + m_forward, m_up);
}

Matrix Camera::getProjectionMatrix() const
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

Vec3 Camera::screenPointToWorldPoint(Vec2 point2D)
{
	int width = GRAPHICS->getWidth();
	int height = GRAPHICS->getHeight();

	Matrix projectionMatrix = getProjectionMatrix();
	Matrix viewMatrix = getViewMatrix();

	Matrix matProjection = projectionMatrix * viewMatrix;
	Matrix matInverse = glm::inverse(matProjection);

	float winZ = 1.0f;

	glm::vec4 vIn = 
	{ 
		2.0f * point2D.x / width - 1.0f,
		-2.0f * point2D.y / height + 1.0f,
		2.0f * winZ - 1.0f,
		1.0f
	};

	glm::vec4 pos = matInverse * vIn;

	pos.w = 1.0f / pos.w;
	pos.x *= pos.w;
	pos.y *= pos.w;
	pos.z *= pos.w;

	return pos;
}