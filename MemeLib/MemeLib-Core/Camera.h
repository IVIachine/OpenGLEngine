#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix.h"
#include <Trackable.h>
#include "GL\glew.h"
class Camera : public Trackable
{
public:
	Camera(const Vec3& pos, float fov, float aspect, float zNear, float zFar);
	~Camera();

	Matrix	getViewProjection() const;
	Matrix	getPerspective() const;
	float	getFOV() const;

	Vec3	getFoward() const;
	Vec3	getPosition() const;
	Vec3	getUp() const;

	void	setForward(Vec3 front);	
	void	setPosition(Vec3 pos);
	float	getNear() { return m_near; };
	float	getFar() { return m_far; };

private:
	Matrix	m_perspective;
	Vec3	m_pos;
	Vec3	m_forward;
	Vec3	m_up;
	float	m_fov, m_far, m_near;
};
#endif
