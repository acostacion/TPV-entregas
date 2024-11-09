#pragma once
#include <fstream>
#include <iostream>
#include <cmath>

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Goomba
{
private:
	Game* game;
	SDL_Renderer* renderer;
	SDL_Rect collider;
	Texture* texturaGoomba;
	Point2D<float> pos;
	Point2D<float> dir;

	bool isGrounded;
	bool startMoving;
	bool dead;

	int timer;
	int anim;
	SDL_Rect collisionRect;
	Collision::collision collisionResult;

	// Submétodos.
	SDL_Rect createRect(int, int, int, int);

public:
	Goomba(Game*, std::istream&);

	const float GRAVITY = 0.1f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.
	const float MAX_FALL_SPEED = 0.2f;

	void render();
	void update();
	Collision::collision hit(const SDL_Rect&, bool);

	// Getter de la posX del Goomba.
	float getX()const { return this->pos.GetX(); }
	bool getMoving()const { return startMoving; }
	Point2D<float> getDir()const { return dir; }


};

