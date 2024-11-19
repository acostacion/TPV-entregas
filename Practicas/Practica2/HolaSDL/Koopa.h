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
	Koopa(Game*, std::istream&);
	void render(SDL_Renderer* renderer)const override;
	void update() override;
	void animation() override;

	Collision hit(const SDL_Rect&, bool) override;

protected:
    void launchShell(const SDL_Rect&);
};


