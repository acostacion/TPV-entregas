#pragma once

#include "Pickable.h"

class Coin: Pickable
{
	Coin();

	void render(SDL_Renderer* renderer)const override;
	void update() override;
	void animation() override;

	Collision hit(const SDL_Rect&, Collision::Target) override;


	void  triggerAction();

	
};

