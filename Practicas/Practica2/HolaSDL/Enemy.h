#pragma once
#include "SceneObject.h"

class Game;

class Enemy : public SceneObject
{
	Game* game;
	Texture* texture;
	SDL_Rect collider;
	Point2D<float> pos;
	Point2D<float> dir;
	bool isGrounded;
	bool frozen;
	bool dead;
	const int MARGIN_Y = 5;
	const int MARGIN_X = 5;

	int timer;
	int anim;
	SDL_Rect createRect(float, float);
};

