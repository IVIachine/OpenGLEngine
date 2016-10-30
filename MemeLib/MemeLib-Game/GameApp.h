#ifndef _GAME_APP_H_
#define _GAME_APP_H_

#include <iostream>
#include "Game.h"
#include "Path.h"
#include "NavMesh.h"
#include "Pathfinder.h"
#include "Graph.h"
#include "ComponentManager.h"
#include "UnitManager.h"
#include "GameController.h"

const int MAX_UNITS = 500;

class GameApp: public EventListener
{
public:
	GameApp();
	~GameApp();

	bool setup(size_t width, size_t height);
	void cleanup();

	bool loadResources();
	void unloadResources();
	virtual void handleEvent(const Event& ev);
	void update();
	void draw();

private:
	float		m_counter;
	Volume*		m_skybox;
	Texture2D*	mp_texture;
	Volume*		mp_volume;
	NavMesh*	mp_navMesh;
	Path		m_path;

	GameController m_controller;
	
};

#endif // !_GAME_APP_H_