#pragma once
#include "Enemy.h"

class Game;
class Goomba : public Enemy
{
private:


public:
	Goomba(Game* , std::istream&, int);

	void render(SDL_Renderer* renderer)const override;
	void update() override;
	void animation() override;

	Collision hit(const SDL_Rect&, Collision::Target) override;
};

