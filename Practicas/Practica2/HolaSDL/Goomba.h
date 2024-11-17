#pragma once
#include <fstream>
#include <iostream>
#include <cmath>

#include "Game.h"
#include "Enemy.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Goomba : public Enemy
{
private:


public:
	Goomba(int x, int y)
		: Enemy(x, y, 16, 16, 100) {}


    virtual void render() const override {
        if (!dead) {
            // Dibujar Goomba normal
            SDL_RenderCopy(game->getRenderer(), game->getTexture(), nullptr, &getRect());
        }
    }

    virtual void update() override {
        Enemy::update(); // Movimiento básico definido en Enemy
    }
};

