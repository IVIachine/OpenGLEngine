#ifndef _GAME_APP_H_
#define _GAME_APP_H_

#include <iostream>
#include "Game.h"
#include "Path.h"
#include "NavigationMesh.h"
#include "Pathfinder.h"
#include "Graph.h"

const int MAX_UNITS = 500;

class GameApp
{
public:
	GameApp();
	~GameApp();

	bool setup(size_t width, size_t height);
	void cleanup();

	void moveCamera(Camera * camera);

	bool loadResources();
	void unloadResources();

	void update();
	void draw();

private:
	float	m_counter;
	Volume*	m_skybox;

	Pathfinder* mpPathfinder;
	Texture2D*	mp_texture;
	Volume*		mp_volume;
	Sprite*		mp_sprite1;
	Sprite*		mp_sprite2;
	NavigationMesh* mNavMesh;
	Vec3		m_position;
	Path		m_path;
};

#endif // !_GAME_APP_H_