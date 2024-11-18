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

    Collision::collision hit(const SDL_Rect&, bool) override;

    void render(SDL_Renderer*) const override;

    void update() override;

protected:
    void launchShell(const SDL_Rect&);
};


