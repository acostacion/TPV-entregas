#pragma once
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Player.h"
#include "Mushroom.h"

class Game;
class Player;
class Mushrrom;

class Blocks
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
	Texture* texturaBlock;
	int animFrame; // indentificador del sprite, 0-3 -> sorpresa, 4 -> vacio, 5 -> ladrillo
	bool anim; // si tiene que animarse, seria solo el sorpresa
	int animTimer;

	void changeSprite();

public:
	Blocks(Game* _game, std::istream& in);

	void render(SDL_Renderer* renderer);
	void update();

	Collision::collision hit(const SDL_Rect& other, bool);

	// Submétodos.
	SDL_Rect createBlockRect();

	bool getDestroyed() const { return destroyed; }


};

