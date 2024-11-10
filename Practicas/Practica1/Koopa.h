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
	Texture* texturaKoopa;
	SDL_Rect collider;
	Point2D<float> pos;
	Point2D<float> dir;
	bool frozen;
	bool dead;
	int anim;

public:
	Koopa(Game*, std::istream&);
	SDL_Rect createRect(float w, float h, float x, float y);
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.

	void render(SDL_Renderer* renderer);
	void update();
	Collision::collision hit(const SDL_Rect&, bool);

	// Getter de la posX del player.
	float getX()const { return this->pos.GetX(); }
	bool getDead()const { return dead; }
	bool getFrozen()const { return frozen; }
	Point2D<float> getDir()const { return dir; }

};

