#pragma once
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"

class Game;
class Blocks
{
public: 
	enum Tipos {
		ladrillo,
		sorpresa,
		vacio,
		oculto,
	};

	enum Accion {
		potenciador,
		moneda,
		nada,
	};

private:
	Game* game;
	Texture* texturaBlock;
	Point2D<float> pos;
	Tipos tp;
	Accion ac;

public:
	Blocks(Game*, std::istream&);

	void render();
	void update();
	void hit();

};

