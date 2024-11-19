#pragma once

#include <fstream>
#include <iostream>
#include <cmath>

#include "Game.h"
#include "Pickable.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Mushroom : Pickable
{
private:


public:
	
	Mushroom(Game *, const Point2D<float>&);
	
	void render(SDL_Renderer* renderer) const override;
	void update() override;
	void triggerAction() override;

	Collision hit(const SDL_Rect&, bool) override;
};

