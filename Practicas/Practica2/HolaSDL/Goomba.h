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
	Goomba(int x, int y) : Enemy(x, y, 16, 16, 100) {}


	void render(SDL_Renderer* renderer)const override;
	void update() override;
	void animation() override;

	Collision hit(const SDL_Rect&, bool) override;
};

