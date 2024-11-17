#pragma once
#include "CheckML.h"
#include "SceneObject.h"

#include <fstream>
#include <iostream>

class Enemy : public SceneObject
{
protected:
	int points;
	bool dead;
	bool frozen;

public:
	Enemy(int x, int y, int width, int height, int points)
		: SceneObject(x, y, width, height), points(points), dead(false) {}

	virtual Collision::collision hit(const SDL_Rect& attackRect, bool isFromPlayer) override {
		if (isFromPlayer && !dead) {
			// Si el ataque proviene del jugador y no ha sido derrotado
			dead = true;
			givePointsToPlayer();
		}
	}

	virtual void update() override {
		if (!dead) {
			tryToMove({ -1, 0 }, true); // Movimiento básico hacia la izquierda
		}
	}

	bool getFrozen()const { return frozen; }
	bool isDead()const { return dead; }

protected:

	virtual void givePointsToPlayer() {
		// Lógica para sumar puntos al jugador
		if (game) {
			game->addPoints(points); 
		}
	}
};

