#pragma once
#include "SceneObject.h"

class Game;

class Blocks : public SceneObject
{
public: 
	enum Tipos { LADRILLO, SORPRESA, VACIO, OCULTO };
	enum Accion { POTENCIADOR, MONEDA, NADA };

private:
	// Enum.
	Tipos tipo = Tipos::LADRILLO;
	Accion action = Accion::NADA;

	// Referencias.
	Texture* texture = nullptr;

	// Propiedades.
	Point2D<float> pos;
	bool destroyed = false;
	SDL_Rect colision; 

	// Gráficos.
	int animFrame = 0; // indentificador del sprite, 0-3 -> sorpresa, 4 -> vacio, 5 -> ladrillo
	bool anim = false; // si tiene que animarse, seria solo el sorpresa
	int animTimer = 3;

	void changeSprite();

public:
	Blocks(Game* _game, std::istream& in);

	void render(SDL_Renderer* renderer) override;
	void update() override;
	Collision::collision hit(const SDL_Rect& other, bool fromPlayer) override;

	// Submétodos.
	SDL_Rect createBlockRect();
	bool getDestroyed() const { return destroyed; }
	void updateAnimation();
};

