#pragma once
#include <fstream>
#include <iostream>
#include <cmath>

#include "Game.h"
#include "Enemy.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Goomba : public Enemy
{
private:


public:
	Goomba(Game*, std::istream&);

	const float GRAVITY = 0.1f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.
	const float MAX_FALL_SPEED = 0.2f;

	void render(SDL_Renderer* renderer) override;
	void update() override;
	Collision::collision hit(const SDL_Rect&, bool);

};

