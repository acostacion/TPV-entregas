#pragma once
#include <fstream>
#include <iostream>
#include <cmath>

#include "CheckML.h"
#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Goomba
{
private:
	Game* game;
	Texture* texturaGoomba;
	Point2D<float> pos;
	Point2D<float> dir;

	bool isGrounded;
	bool frozen;
	bool dead;
	const int MARGIN_Y = 5;
	const int MARGIN_X = 5;

	int timer;
	int anim;
	Collision::collision collisionResult;

	// Submétodos.
	SDL_Rect createRect(float, float);

public:
	Goomba(Game*, std::istream&);

	const float GRAVITY = 0.1f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.
	const float MAX_FALL_SPEED = 0.2f;

	void render(SDL_Renderer* renderer);
	void update();
	Collision::collision hit(const SDL_Rect&, bool);

	// Getter de la posX del Goomba.
	float getX()const { return this->pos.GetX(); }
	bool getFrozen()const { return frozen; }
	Point2D<float> getDir()const { return dir; }

	bool isDead()const { return dead; }
};

