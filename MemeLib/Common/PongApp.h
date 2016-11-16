#ifndef _PONG_APP_H_
#define _PONG_APP_H_

#include <Game.h>
#include <Application.h>

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
};

#endif // !_PONG_APP_H_
