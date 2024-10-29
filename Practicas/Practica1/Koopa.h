#pragma once
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"

class Game;
class Koopa
{
private:
	Game* game;
	Texture* texturaKoopa;
	Point2D<float> pos;
	Point2D<float> dir;
	bool startMoving;
	bool dead;
	int anim;

public:
	Koopa(Game*, std::istream&);

	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.

	void render();
	void update();
	void hit();

	// Getter de la posX del player.
	float getX()const { return this->pos.GetX(); }
	bool getMoving()const { return startMoving; }
	Point2D<float> getDir()const { return dir; }

};

