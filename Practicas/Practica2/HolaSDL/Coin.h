#pragma once


#include "Game.h"
#include "Pickable.h"
#include "Vector2D.h"
#include "Collision.h"

class Coin: Pickable
{
	Coin();

	void render(SDL_Renderer* renderer)const override;
	void update() override;
	void animation() override;

	Collision hit(const SDL_Rect&, bool) override;
};

