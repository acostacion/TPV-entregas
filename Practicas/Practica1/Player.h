#pragma once
#include <fstream>
#include <iostream>
#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
static const Point2D<float> DIR_INI{ 0, 0 };

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
	Point2D<float> posIni;
	Point2D<float> posInicio;

	float verticalVelocity;
	int altura;

	bool isGrounded; // si esta en el suelo
	bool isJumping;
	
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
	SDL_Rect getCollider(bool forRender) const;
	void changeMario();
	void jump();
	void decreaseLife();
	
#pragma endregion

#pragma region Constants

	//CONSTANTES.
	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const float JUMP_FORCE = -1.0f; // fuerza de salto.
	const float MAX_FALL_SPEED = 0.2f; // velocidad de caída máxima.
	const int MAX_ALTURA = 15; // velocidad de caída máxima.
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
	bool isSuperMario()const; // obtener si es superMario o no.

	//metodos que devuelven la posicion y direccion para detectar colisiones
	Point2D<float> getPlayerPos();
	Point2D<float> getPlayerDir();

	//metodo auxiliare que devuelve si es un supermario

	int getPlayerLife() const;

	void resetPos();

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


