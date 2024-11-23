#pragma once
#include "Enemy.h"

class Goomba : public Enemy
{
public:
	Goomba(Game* game, std::istream& in);

	void render(SDL_Renderer* renderer) override;
	void update() override;
};

