#pragma once
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Koopa
{
private:
	Game* game;
	SDL_Renderer* renderer;
	Texture* texturaKoopa;
	SDL_Rect collider;
	Point2D<float> pos;
	Point2D<float> dir;
	bool startMoving;
	bool dead;
	int anim;

public:
	Koopa(Game*, std::istream&);
	SDL_Rect createRect(float w, float h, float x, float y);
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.

	void render();
	void update();
	Collision::collision hit(const SDL_Rect&, bool);

	// Getter de la posX del player.
	float getX()const { return this->pos.GetX(); }
	bool getMoving()const { return startMoving; }
	Point2D<float> getDir()const { return dir; }

};

