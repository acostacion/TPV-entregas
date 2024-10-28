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
		vacío,
		oculto,
	};

	enum Accion {
		potenciador,
		moneda,
	};

private:
	Game* game;
	Texture* texturaGoomba;
	Point2D<float> pos;

public:
	Blocks(Game*, std::istream&);


	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const float JUMP_FORCE = -1.0f; // fuerza de salto.
	const float MAX_FALL_SPEED = 0.2f; // velocidad de caída máxima.
	const float DECELERATION = 0.0005f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.

	void render();
	void update();
	void hit();

	// Getter de la posX del player.
	float getX()const { return this->pos.GetX(); }

};

