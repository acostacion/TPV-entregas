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
	bool isGrounded;

public:
	Player(Game*, std::istream&);

	const float GRAVITY = 0.01f; // gravedad.

	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const float JUMP_FORCE = -0.7f; // fuerza de salto.
	const float MAX_FALL_SPEED = 0.2f; // velocidad de caída máxima.

	const float MOVE_SPEED = 0.05f; // velocidad de movimiento.

	void render();
	void update();
	void hit();
	void handleEvent(SDL_Event);

	// Getter de la posX del player.
	float getX()const { return this->pos.GetX(); }

	// Setter de la posX del player.
	void setX(float _x)const { pos.SetX(_x); }


};

