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
	Koopa();
    virtual Collision::collision hit(const SDL_Rect& attackRect, bool isFromPlayer) override {
        if (!dead) {
            if (isShell) {
                // Si est� en forma de caparaz�n, se lanza como proyectil
                launchShell(attackRect);
            }
            else {
                // Cambiar a forma de caparaz�n
                isShell = true;
                points = 0; // Sin puntos por cambiar de forma
                // Cambiar sprite o animaci�n
            }
        }
        else {
            Enemy::hit(attackRect, isFromPlayer); // Comportamiento base
        }
    }

    virtual void render() const override {
        if (!dead) {
            const char* texture = isShell ? "koopa_shell" : "koopa";
            SDL_RenderCopy(game->getRenderer(), game->getTexture(texture), nullptr, &getRect());
        }
    }

    virtual void update() override {
        if (!isShell) {
            Enemy::update(); // Movimiento base para Koopa normal
        }
        else {
            tryToMove({ 2, 0 }, true); // Movimiento de caparaz�n si es lanzado
        }
    }

protected:
    void launchShell(const SDL_Rect& attackRect) {
        // L�gica para lanzar la caparaz�n como proyectil
        int direction = attackRect.x < position.x ? 1 : -1;
        velocity.x = direction * 5; // Velocidad del caparaz�n
    }
};


