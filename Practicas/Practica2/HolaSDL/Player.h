#pragma once
#include "CheckML.h"
#include "SceneObject.h"

// para evitar inclusiones cruzadas.
class Game; 

static const Point2D<float> DIR_INI{ 0, 0 };
class Player : public SceneObject
{
private:
	// REFERENCES.
	Game* game = nullptr;
	Texture* texture = nullptr;

	// PARAMETERS.
	Point2D<float> pos;
	Point2D<float> dir;
	Point2D<float> posInicio;// para el reinicio

	bool isGrounded; // si esta en el suelo
	bool isJumping;
	bool superMario = false;
	bool dead;

	
	float verticalVelocity;

	int life;
	int anim; // indice del frame de la animacion
	int margenColi = 9;

	// CONSTANTS.
	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const int MAX_HEIGHT = 15; // altuma maxima de salto
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.

public:

	Player(Game*, std::istream&); // constructora

	void render(SDL_Renderer* _renderer) override;
	void update() override;
	void handleEvent(SDL_Event);
	Collision::collision hit(const SDL_Rect& otherRect, bool fromPlayer) override;

private:
	// METHODS.
	SDL_Rect createRect(float, float, float, float);
	SDL_Rect getRect(bool forRender) const;
	
	void resetPos(); // reinicia pos del player.
	void decreaseLife();
	void jump();

	void renderMarioAnimation(const SDL_Rect&, SDL_Renderer*);

	// Mario swapping.
	void setSuperMario();
	void setOnlyMario();
	void changeMario();
	
	// Getters
	float getX() const { return this->pos.GetX(); }
	float getY()const { return this->pos.GetY(); }
	Point2D<float> getPlayerPos() { return pos; }
	Point2D<float> getPlayerDir() { return dir; }
	int getPlayerLife() const { return life; }
	bool isDead()const { return life <= 0; } // Est? vivo si life >0.
	bool isSuperMario()const { return superMario; }
};


