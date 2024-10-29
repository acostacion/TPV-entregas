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
	bool isGrounded;
	bool movingDer;
	bool moving;
	int anim;
	SDL_RendererFlip flip;

public:
	Player(Game*, std::istream&);

	const float GRAVITY = 0.1f; // gravedad.

	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const float JUMP_FORCE = -1.0f; // fuerza de salto.
	const float MAX_FALL_SPEED = 0.2f; // velocidad de caída máxima.
	const float DECELERATION = 0.0005f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.

	void render();
	void update();
	void hit();
	void handleEvent(SDL_Event);

	// Getter de la posX del player.
	float getX()const { return this->pos.GetX(); }
	bool getMovingDer()const { return movingDer; }
	Point2D<float> getDir()const { return dir; }

	

};

