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
	Tipos tipo; // ladrillo, sorpresa, vacio, oculto
	Accion action; // potenciador, moneda, nada
	int fx; // indentificador del sprite, 0-3 -> sorpresa, 4 -> vacio, 5 -> ladrillo
	bool anim; // si tiene que animarse, seria solo el sorpresa
	int timer;
public:
	Blocks(Game*, std::istream&);

	void render();
	void update();
	void hit();

};

