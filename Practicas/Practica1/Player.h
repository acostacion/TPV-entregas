#pragma once
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"

class Game;
class Player
{
private:
	Game* game;
	Texture* texturaMario;
	Texture* texturaSMario;
	Point2D<float> pos;
	int life;
	Point2D<float> dir;
	bool superMario;
	bool jumping;
	bool onGround;

public:
	Player(Game*, std::istream&);
	const float GRAVITY = 0.01f;
	const float JUMP_FORCE = -0.7f;
	const float MAX_FALL_SPEED = 0.2f;
	const float MOVE_SPEED = 0.05f;
	const float MAX_HORIZONTAL_SPEED = 0.1f;
	const float ACCELERATION = 0.005f;
	void render();
	void update();
	void hit();
	void handleEvent(SDL_Event);

};

