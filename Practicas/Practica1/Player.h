#pragma once
#include <fstream>
#include <iostream>
#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;

class Player{
private:
#pragma region References
	Game* game;
	Texture* texturaMario;
	Texture* texturaSMario;
#pragma endregion

#pragma region Movement

	Point2D<float> dir;
	Point2D<float> pos;
	Point2D<float> posInicio;
	float verticalVelocity;
	bool isGrounded; // si esta en el suelo
	bool movingDer; // si se esta moviendo a la derecha, se usa en el game para saber si mueve el mapoffset y que no se mueva infinitamente si esta en ese borde

#pragma endregion

#pragma region Collision

	SDL_Rect collider;
	Collision::collision collisionRes;

#pragma endregion

#pragma region Animation
	int anim; // indice del frame de la animacion

#pragma endregion

#pragma region Atributes

	int invulnerableTimer;
	int life;
	int margenColi = 9;
	bool superMario = false;
	bool invulnerable;

#pragma endregion

	
#pragma region Methods

	SDL_Rect createRect(float, float, float, float);
	void resetPos();
	SDL_Rect getCollider(bool forRender) const;
	SDL_Rect getNextCollider(int x, int y) const;
	void animation();
	void changeMario();
	void jump();
	void decreaseLife();
	
#pragma endregion

#pragma region Constants

	//CONSTANTES.
	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const float JUMP_FORCE = -1.0f; // fuerza de salto.
	const float MAX_FALL_SPEED = 0.2f; // velocidad de ca�da m�xima.
	const float DECELERATION = 0.0005f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.
	const float COLLISION_OFFSET = 0.3f; // velocidad de movimiento.
	const float GROUND_LEVEL = 12.9f;
	const float GRAVITY = 1.0f; // gravedad.

#pragma endregion


public:
	Player(Game*, std::istream&);

	void render(SDL_Renderer* renderer);
	void update();
	void handleEvent(SDL_Event);
	Collision::collision hit(const SDL_Rect otherRect);

	// Getters
	float getX()const { return this->pos.GetX(); }
	Point2D<float> getPos() const { return this->pos; }
	bool getMovingDer()const { return movingDer; }
	Point2D<float> getDir()const { return dir; }
	bool isSuperMario()const; // obtener si es superMario o no.

	//metodos que devuelven la posicion y direccion para detectar colisiones
	Point2D<float> getPlayerPos();
	Point2D<float> getPlayerDir();

	//metodo auxiliare que devuelve si es un supermario
	bool esSuperMario() const;

	int getPlayerLife() const;

	void resetPlayerPos();

};


inline bool
Player::isSuperMario() const {
	return superMario;
}

inline Point2D<float>
Player::getPlayerPos() {
	return pos;
}

inline Point2D<float>
Player::getPlayerDir() {
	return dir;
}
inline int
Player::getPlayerLife() const {
	return life;
}


