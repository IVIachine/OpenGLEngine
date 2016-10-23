#ifndef _GAME_APP_H_
#define _GAME_APP_H_

#include <iostream>
#include "Game.h"

const int MAX_UNITS = 500;

class GameApp
{
public:
	GameApp();
	~GameApp();

	bool setup(size_t width, size_t height);
	void cleanup();

	bool loadResources();
	void unloadResources();

	void update();
	void draw();

private:
	float	m_counter;
	Volume*	m_skybox;

	Texture2D*	mp_texture;
	Volume*		mp_volume;
	Sprite*		mp_sprite1;
	Sprite*		mp_sprite2;
	Vector2		m_position;
};

#endif // !_GAME_APP_H_