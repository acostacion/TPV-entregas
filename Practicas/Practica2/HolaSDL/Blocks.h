#pragma once
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"
#include "SceneObject.h"
#include "Mushroom.h"

class Game;
class Mushrrom;

class Blocks : SceneObject
{
public: 
	enum Variant { ladrillo, sorpresa, vacio, oculto };
	enum Action { potenciador, moneda, nada };

private:

	// Propiedades.
	bool destroyed = false;
	int animFrame;
	Variant tipo; // ladrillo, sorpresa, vacio, oculto.
	Action action; // potenciador, moneda, nada.

	// Gráficos.

	void changeSprite();

public:
	Blocks(Game* _game, std::istream& in);
	void animation() override;
	void render(SDL_Renderer* renderer)const override;
	void update()override;

	Collision::collision hit(const SDL_Rect& other, bool);

	// Submétodos.

	bool getDestroyed() const { return destroyed; }

};

