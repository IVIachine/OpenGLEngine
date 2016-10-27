#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include <gtx\transform.hpp>
#include <Trackable.h>

class Camera : public Trackable
{
public:
	Camera(const Vec3& pos, float fov, float aspect, float zNear, float zFar);
	~Camera();

	glm::mat4	getViewProjection() const;
	glm::mat4	getPerspective() const;

	float		getFOV() const;
	void		setPos(Vec3 pos);

	Vec3	getPos();
	Vec3	getFowardVector();
	Vec3	getUpVector();
	void		setFront(Vec3 front);	

private:
	glm::mat4	m_perspective;
	Vec3	m_pos;
	Vec3	m_forward; //Camera rotations
	Vec3	m_up;
	float		m_fov;
};
#endif
