#pragma once
#include <fstream>
#include <iostream>

#include "Enemy.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;

class Koopa : public Enemy
{
private:
	Game* game;
	Texture* texturaKoopa;
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

public:
	Koopa(Game*, std::istream&);

	const float GRAVITY = 0.1f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.
	const float MAX_FALL_SPEED = 0.2f;

	void render(SDL_Renderer* renderer) override;
	void update() override;
	Collision::collision hit(const SDL_Rect&, bool) override;

	// Getter de la posX del Goomba.
	float getX()const { return this->pos.GetX(); }
	bool getFrozen()const { return frozen; }
	Point2D<float> getDir()const { return dir; }

	bool isDead()const { return dead; }

};

