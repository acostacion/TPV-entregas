#pragma once
#include "checkML.h"	
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"

/*
* virtual: para indicar que un método se puede sobreescribir por subclases. virtual tipo method() = 0;
* override: para indicar la sobreescritura de la clase base.
*/

class Game;

class GameObject{
protected:
	// Atributos.
	Game* game;

public:
	// Métodos.
	//GameObject(Game* _game) { game = _game; }

	virtual void render(SDL_Renderer* renderer)const = 0;

	virtual void update() = 0;

	virtual ~GameObject() {}
};

