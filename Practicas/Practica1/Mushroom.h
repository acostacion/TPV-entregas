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
	Texture* texturaMushroom;
	Point2D<float> pos;
	Point2D<float> dir;

	bool isGrounded;
	bool dead;

	SDL_Rect getRect(bool) const;
	SDL_Rect createRect(float, float);
public:
	Mushroom(Game *, float, float); // No tengo claro q ha de ir en la constructora, se leería con std??
	void render(SDL_Renderer* renderer);
	void update();
	Collision::collision hit(const SDL_Rect&, bool);

	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.


	// Getter de la posX del mushroom.
	float getX()const { return this->pos.GetX(); }
	Point2D<float> getDir()const { return dir; }

};

