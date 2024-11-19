#pragma once
#include "Pickable.h"

class Game;

class Mushroom : Pickable
{
private:


public:
	
	Mushroom(Game *, const Point2D<float>&);
	
	void render(SDL_Renderer* renderer) const override;
	void update() override;
	void triggerAction() override;
	void animation() override;

	Collision hit(const SDL_Rect&, Collision::Target) override;
};

