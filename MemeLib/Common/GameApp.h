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
#include "Application.h"
#include "PickupSpawner.h"

const int MAX_UNITS = 500;

class GameApp : public Application
{
public:
	GameApp();
	~GameApp();

	bool setup() override;
	void clear() override;
	void update() override;
	void draw() override;
	void handleEvent(const Event& ev) override;



private:
	Volume*		m_skybox;
	Texture2D*	mp_texture;
	Volume*		mp_volume;

	NavMesh*	mp_navMesh;
	MousePicker* mp_picker;

	GLuint tex;
	GameController m_controller;	
	PickupSpawner* mp_spawner;
};

#endif // !_GAME_APP_H_