#pragma once
#include <fstream>
#include <iostream>
#include <cmath>

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Mushroom
{
	// pos, dir, textura, game.

private:
	Game* game;
	SDL_Rect collider;
	Texture* texturaMushroom;
	Point2D<float> pos;
	Point2D<float> dir;

	bool isGrounded;
	bool dead;

	int timer;
	int anim;
	SDL_Rect collisionRect;
public:
	Mushroom(); // No tengo claro q ha de ir en la constructora, se leería con std??
	void render(SDL_Renderer* renderer);
	void update();
	Collision::collision hit(const SDL_Rect&, bool);

	// Getter de la posX del mushroom.
	float getX()const { return this->pos.GetX(); }
	Point2D<float> getDir()const { return dir; }

};

