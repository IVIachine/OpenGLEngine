#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

class Camera;
class NavMesh;
class Node;

class GameController
{
public:
	GameController() {}
	~GameController() {}

	void update(NavMesh* pNavMesh);
	void draw(NavMesh* pNavMesh);

	void moveCamera(Camera* pCamera);

private:
	int			m_index = 0;
	Node*		mp_target;
};

#endif // !_GAME_CONTROLLER_H_
