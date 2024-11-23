#pragma once
#include "Enemy.h"

class Koopa : public Enemy{
public:
	Koopa(Game*, std::istream& in);

	void render(SDL_Renderer* renderer) override;
	void update() override;
};

