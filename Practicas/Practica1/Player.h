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

public:
	Player(Game*, std::istream&);

	void render();
	void update();
	void hit();
	void handleEvent();

};

