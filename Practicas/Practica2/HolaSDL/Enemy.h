#pragma once
#include "SceneObject.h"
#include "Game.h"

class Game;

static const Point2D<float> DIR_INI{ -1, 0 };
class Enemy : public SceneObject
{
protected:
	int points;
	bool frozen;

public:
	Enemy(Game* , std::istream& , int );

	virtual	void render(SDL_Renderer* renderer) const override;
	virtual void update() override;
	virtual Collision hit(const SDL_Rect&, Collision::Target) override;
	virtual void animation() override;

	bool getFrozen()const { return frozen; }

protected:

	virtual void givePointsToPlayer();
};

