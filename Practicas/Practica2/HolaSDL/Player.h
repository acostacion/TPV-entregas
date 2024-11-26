#pragma once
#include "SceneObject.h"

// para evitar inclusiones cruzadas.
class Game; 
static const Point2D<float> DIR_INI{ 0, 0 };

class Player : public SceneObject
{
private:
	// References.
	Game* game = nullptr;
	Texture* texture = nullptr;

	// Parameters.
	Point2D<float> pos;
	Point2D<float> dir = DIR_INI;
	Point2D<float> posInicio;// para el reinicio

	bool isGrounded = false; // si esta en el suelo
	bool isJumping = false;
	bool superMario = false;
	bool dead = false;

	
	float verticalVelocity = 0;
	int life = 0;
	int anim = 0; // indice del frame de la animacion


	// Constans.
	// En sdl ir para arriba es negativo e ir para abajo es positivo.
	const int MARGEN_COLI = 9;
	const int MAX_HEIGHT = 15; // altuma maxima de salto
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.

public:

	// Main Methods.
	Player(Game* _game, std::istream& in); 

	void render(SDL_Renderer* _renderer) override;
	void update() override;
	void handleEvent(SDL_Event _event);
	Collision hit(const SDL_Rect& otherRect, Collision::Target target) override;

	// Other Methods.
	bool isDead() { return life <= 0; }
	void resetPosition() { pos = posInicio; }
	Point2D<float> getDir() { return dir; }

private:
	// Submethods.
	SDL_Rect createRect(float x, float y, float h, float w);
	SDL_Rect getRect(bool forRender) const;

	void decreaseLife();
	void jump();
	void renderAnimation(const SDL_Rect& rect, SDL_Renderer* renderer);
	void updateAnimation();
	void setSuperMario(bool isSuperMario);
};


