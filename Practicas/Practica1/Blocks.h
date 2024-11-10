#pragma once
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Player.h"

class Game;
class Player;
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
	Player* player; // referencia al player.
	SDL_Rect collider;
	Game* game;
	Texture* texturaBlock;
	Point2D<float> pos; 
	Tipos tipo; // ladrillo, sorpresa, vacio, oculto
	Accion action; // potenciador, moneda, nada
	int animFrame; // indentificador del sprite, 0-3 -> sorpresa, 4 -> vacio, 5 -> ladrillo
	bool anim; // si tiene que animarse, seria solo el sorpresa
	int timer;
public:
	Blocks(Game*, std::istream&);

	void render();
	void update();
	Collision::collision hit(const SDL_Rect&, bool);

	// Submétodos.
	SDL_Rect createBlockRect();

};

