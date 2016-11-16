#ifndef _PONG_APP_H_
#define _PONG_APP_H_

#include <Game.h>
#include <Application.h>

struct PongObj
{
	Sprite* sprite;
	Vec3 position;
};

class PongApp : public Application
{
public:
	PongApp();
	~PongApp();

	bool setup() override;
	void clear() override;
	void update() override;
	void draw() override;
	void handleEvent(const Event& ev) override;

private:
	PongObj	m_paddle1;
	PongObj	m_paddle2;
	PongObj	m_ball;
};

#endif // !_PONG_APP_H_
