#pragma once
#include "SceneObject.h"
#include <fstream>
#include <iostream>
#include "Texture.h"

static const Point2D<float> DIR_INI{ 0, 0 };

class Player : public SceneObject{
private:
#pragma region References
	Texture* texturaMario; //mario
	Texture* texturaSMario; // superMario

#pragma endregion

#pragma region Parameters

	// MOVIMIENTO.
	Point2D<float> dir;
	Point2D<float> posInicio;// para el reinicio

	bool isGrounded; // si esta en el suelo
	bool isJumping;

	float verticalVelocity;

	// ANIMACIÓN.
	int anim; // indice del frame de la animacion

	// ATRIBUTOS.
	int life;
	int margenColi = 9;
	bool superMario = false;
	bool dead;
	
#pragma endregion

#pragma region Constants

	//CONSTANTES.
	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const int MAX_HEIGHT = 15; // altuma maxima de salto
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.

#pragma endregion
	
#pragma region Methods

	SDL_Rect createRect(float, float);
	SDL_Rect getRect(bool forRender) const;
	void changeMario();
	void jump();
	void decreaseLife();
	
#pragma endregion

public:
	
	Player(Game* game, std::istream& in); // constructora

	void render(SDL_Renderer* renderer)const override;
	void update() override;
	void handleEvent(SDL_Event);
	Collision::collision hit(const SDL_Rect& otherRect, bool fromPlayer) override;

	void resetPos();

	// Getters.
	void renderMarioAnimation(const SDL_Rect&, SDL_Renderer*) const;
	bool isDead()const { return dead; } // Está vivo si life >0.
	bool isSuperMario() const { return superMario; }

	//metodos que devuelven la posicion y direccion para detectar colisiones.
	Point2D<float> getPlayerPos() { return pos; }
	Point2D<float> getPlayerDir() { return dir; }

	int getPlayerLife() const { return life; }
};




