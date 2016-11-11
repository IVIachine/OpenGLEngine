#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "MousePicker.h"

class Camera;
class NavMesh;
class Node;
class Timer;

class GameController
{
public:
	GameController();
	~GameController() {};

	void update(NavMesh* pNavMesh);
	void draw(NavMesh* pNavMesh, MousePicker* picker);

	void moveCamera(Camera* pCamera);

private:
	int			m_index = 0;
	Node*		mp_target;
	bool		mDebugMode = false;
	Timer*		tmp;
	int currentIndex = 0;
};

#endif // !_GAME_CONTROLLER_H_
