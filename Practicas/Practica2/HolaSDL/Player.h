#pragma once
#include "CheckML.h"
#include "SceneObject.h"

#include <fstream>
#include <iostream>

#include "Vector2D.h"
#include "Collision.h"

static const Point2D<float> DIR_INI{ 0, 0 };
class Player : public SceneObject
{
private:
	Texture* texturaMario; //mario
	Texture* texturaSMario; // superMario

	// PARAMETERS.
	Point2D<float> dir;
	Point2D<float> posInicio;// para el reinicio
	bool isGrounded; // si esta en el suelo
	bool isJumping;
	bool superMario = false;
	bool dead;
	int life;
	float verticalVelocity;
	int anim; // indice del frame de la animacion
	int margenColi = 9;

	// CONSTANTS.
	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const int MAX_HEIGHT = 15; // altuma maxima de salto
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.

public:

	Player(std::istream&); // constructora

	void render(SDL_Renderer*);
	void update();
	void handleEvent(SDL_Event);
	Collision::collision hit(const SDL_Rect);

private:
	// METHODS.
	SDL_Rect createRect(float, float, float, float);
	SDL_Rect getRect(bool forRender) const;
	void changeMario();
	void resetPos(); // reinicia pos del player.
	void decreaseLife();
	void jump();

	void renderMarioAnimation(const SDL_Rect&, SDL_Renderer*) const;
	
	float getX() const { return this->pos.GetX(); }
	Point2D<float> getPlayerPos();
	Point2D<float> getPlayerDir();
	int getPlayerLife() const;
	bool isDead()const { return dead; } // Est? vivo si life >0.
	bool isSuperMario()const;

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

