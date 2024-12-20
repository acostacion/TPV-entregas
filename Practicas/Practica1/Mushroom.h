#pragma once
#include "CheckML.h"

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

	bool dead;

	const float MOVE_SPEED = 0.1f; // velocidad de movimiento.
	const float GRAVITY = 0.2;
	const int MARGIN_Y = 5;
	const int MARGIN_X = 5;
	const float MOVE_SPEED_X = 0.1;
	const float MOVE_SPEED_Y = 0.175;
	const float FALL_OFFSET = 0.06;
	
	SDL_Rect createRect(int, int) const;
public:
	Mushroom(Game *, const Point2D<float>&); // No tengo claro q ha de ir en la constructora, se leer�a con std??
	void render(SDL_Renderer* renderer);
	void update();
	Collision::collision hit(const SDL_Rect&, bool);

	bool isDead()const { return dead; }

};

