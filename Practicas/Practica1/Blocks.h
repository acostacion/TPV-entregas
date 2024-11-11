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
	// REFERENCES.
	Player* player; 
	Game* game;

	// COSAS DEL BLOCK.
	Point2D<float> pos;
	SDL_Rect collider;
	bool destroied = false;

	// ENUMS.
	Tipos tipo; // ladrillo, sorpresa, vacio, oculto
	Accion action; // potenciador, moneda, nada

	// ANIMACIONES Y TEXTURAS.
	Texture* texturaBlock;
	int animFrame; // indentificador del sprite, 0-3 -> sorpresa, 4 -> vacio, 5 -> ladrillo
	bool anim; // si tiene que animarse, seria solo el sorpresa
	int animTimer;

public:
	Blocks(Game*, std::istream&);

	void render(SDL_Renderer* renderer);
	void update();

	Collision::collision hit(const SDL_Rect&, bool);

	// Subm�todos.
	SDL_Rect createBlockRect();

	bool getDestroied() const { return destroied; }

};

