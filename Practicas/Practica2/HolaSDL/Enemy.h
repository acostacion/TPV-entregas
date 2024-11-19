#pragma once
#include "CheckML.h"
#include "SceneObject.h"

#include <fstream>
#include <iostream>

static const Point2D<float> DIR_INI{ -1, 0 };

class Enemy : public SceneObject
{
protected:
	int points;
	bool frozen;

public:
	Enemy(Game* _game, std::istream entrada, int points);

	virtual	void render(SDL_Renderer* renderer) const override;
	virtual void update() override;
	virtual Collision hit(const SDL_Rect&, bool) override;
	virtual void animation() override;

	bool getFrozen()const { return frozen; }

protected:

	virtual void givePointsToPlayer() {
		// Lógica para sumar puntos al jugador
		if (game) {
			game->addPoints(points); 
		}
	}
};

