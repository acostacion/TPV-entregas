#pragma once
#include "SceneObject.h"

static const Point2D<float> DIR_INI_PLAYER{ 0, 0 };
class Game;

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

	void handleEvent(SDL_Event);
	void render(SDL_Renderer* renderer)const override;
	void update() override;
	void animation() override;

	Collision hit(const SDL_Rect&, Collision::Target) override;

	// Getters
	float getX() const { return this->pos.GetX(); }
	bool isSuperMario()const; // obtener si es superMario o no.

	//metodos que devuelven la posicion y direccion para detectar colisiones
	Point2D<float> getPlayerPos() { return pos; }
	Point2D<float> getPlayerDir() { return dir; }

	//metodo auxiliare que devuelve si es un supermario

	int getLives() const;

	void resetPos();

	void renderMarioAnimation(const SDL_Rect&, SDL_Renderer*) const;

};

inline bool
Player::isSuperMario() const {
	return superMario;
}

inline int
Player::getLives() const {
	return life;
}