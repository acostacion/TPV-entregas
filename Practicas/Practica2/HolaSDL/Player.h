#pragma once
#include "CheckML.h"

#include <fstream>
#include <iostream>

#include "Game.h"
#include "SceneObject.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;
static const Point2D<float> DIR_INI_PLAYER{ 0, 0 };

class Player : SceneObject {
private:

#pragma region Movement

	Point2D<float> posInicio;// para el reinicio
	bool isJumping;
	float height;

#pragma endregion

#pragma region Atributes

	int life;
	int margenColi = 9;
	bool superMario = false;

#pragma endregion


#pragma region Methods

	void changeMario();
	void jump();
	void decreaseLife();

#pragma endregion

#pragma region Constants

	//CONSTANTES.
	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const int MAX_HEIGHT = 15; // altuma maxima de salto
	
#pragma endregion


public:

	Player(Game*, std::istream&); // constructora

	void render(SDL_Renderer* renderer);
	void update();
	void handleEvent(SDL_Event);
	Collision::collision hit(const SDL_Rect otherRect);

	// Getters
	float getX() const { return this->pos.GetX(); }
	bool isSuperMario()const; // obtener si es superMario o no.

	//metodos que devuelven la posicion y direccion para detectar colisiones
	Point2D<float> getPlayerPos();
	Point2D<float> getPlayerDir();

	//metodo auxiliare que devuelve si es un supermario

	int getPlayerLife() const;

	void resetPos();

	void renderMarioAnimation(const SDL_Rect&, SDL_Renderer*) const;

	bool isDead()const { return dead; } // Est? vivo si life >0.
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