#pragma once
#include "SceneObject.h"

class Game;

class Blocks : public SceneObject
{
public: 
	enum Tipos { ladrillo, sorpresa, vacio, oculto };
	enum Accion { potenciador, moneda, nada };

private:

	// Propiedades.
	Point2D<float> pos;
	bool destroyed = false;
	SDL_Rect colision; 

	Tipos tipo; // ladrillo, sorpresa, vacio, oculto.
	Accion action; // potenciador, moneda, nada.

	// Gráficos.
	Texture* texture;
	int animFrame; // indentificador del sprite, 0-3 -> sorpresa, 4 -> vacio, 5 -> ladrillo
	bool anim; // si tiene que animarse, seria solo el sorpresa
	int animTimer;

	void changeSprite();

public:
	Blocks(Game* _game, std::istream& in);

	void render(SDL_Renderer* renderer) override;
	void update() override;

	Collision::collision hit(const SDL_Rect& other, bool fromPlayer) override;

	// Submétodos.
	SDL_Rect createBlockRect();

	bool getDestroyed() const { return destroyed; }


};

