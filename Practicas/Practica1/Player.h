#pragma once
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
class Player
{
private:
	Game* game;
	SDL_Renderer* renderer;
	Texture* texturaMario;
	Texture* texturaSMario;
	Point2D<float> dir;
	Point2D<float> pos;
	SDL_Rect collider;
	Collision::collision collisionRes;
	int life;
	bool superMario;
	bool isGrounded; // si esta en el suelo
	bool movingDer; // si se esta moviendo a la derecha, se usa en el game para saber si mueve el mapoffset y que no se mueva infinitamente si esta en ese borde
	bool moving; // si se mueve para la animacion
	int anim; // indice del frame de la animacion
	SDL_RendererFlip flip; // para que se gire horizontalmente la animacion

	// Submétodos.
	SDL_Rect createRect(float, float, float, float);

public:
	Player(Game*, std::istream&);

	const float GRAVITY = 0.1f; // gravedad.

	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const float JUMP_FORCE = -1.0f; // fuerza de salto.
	const float MAX_FALL_SPEED = 0.2f; // velocidad de caída máxima.
	const float DECELERATION = 0.0005f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.
	const float COLLISION_OFFSET = 0.3f; // velocidad de movimiento.

	void render();
	void update();
	Collision::collision hit(const SDL_Rect otherRect);
	void handleEvent(SDL_Event);

	// Getter de la posX del player.
	float getX()const { return this->pos.GetX(); }
	Point2D<float> getPos() const { return this->pos; }
	bool getMovingDer()const { return movingDer; }
	Point2D<float> getDir()const { return dir; }

	
	

};

