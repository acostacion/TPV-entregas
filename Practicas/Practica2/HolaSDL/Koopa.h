#pragma once
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Koopa : public Enemy
{
private:
	bool isShell;

public:
	Koopa(Game*, std::istream&, int);
	void render(SDL_Renderer* renderer)const override;
	void animation() override;

	Collision hit(const SDL_Rect&, Collision::Target) override;

protected:
    void launchShell(const SDL_Rect&);
};


