#pragma once
#include "GameObject.h"
#include "Vector3.h"
#include <Rect.h>

class BallServer :public GameObject
{
public:
	BallServer();
	~BallServer();

	enum { mClassId = 'BALL' };
	virtual uint32_t getClassId() const { return mClassId; };

	virtual void write(RakNet::BitStream& stream) const;
	virtual void sendToServer(RakNet::BitStream & stream);
	virtual void sendToServer(RakNet::RakPeerInterface * peer);
	virtual void read(RakNet::BitStream& stream);
	virtual void writeToFile(std::ofstream& of);
	virtual void draw();
	virtual void update();

	Vec3 getLoc() const { return m_pos; };
	void setLoc(Vec3 loc) 
	{
		m_pos = loc; 
	};

	void flip()
	{
		m_vel.y = -m_vel.y;
	};

	void bounce()
	{
		float sign = m_vel.x > 0.f ? 1.f : -1.f;

		float paddle1Y = m_pos.y;
		float PADDLEHEIGHT = 1.0f;
		float intersectY = 0;

		float relativeIntersectY = (paddle1Y + (PADDLEHEIGHT / 2)) - intersectY;
		float normalizedRelativeIntersectionY = (relativeIntersectY / (PADDLEHEIGHT / 2));
		float bounceAngle = normalizedRelativeIntersectionY * m_maxBounceAngle;

		float ballVx = m_ballSpeed * cosf(bounceAngle);
		float ballVy = m_ballSpeed * -sinf(bounceAngle);

		m_vel = Vec3(ballVx, ballVy, 0.f);

		float sign2 = m_vel.x > 0.f ? 1.f : -1.f;
		if (sign == sign2)
		{
			m_vel.x = -m_vel.x;
		}
	};

private:
	Vec3 m_pos;
	Vec3 m_vel;
	float m_maxBounceAngle = 35.f;
	float m_ballSpeed;
};

