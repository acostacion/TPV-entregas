#pragma once
#include "Game.h"
#include <SDL.h>

/*
* virtual: para indicar que un método se puede sobreescribir por subclases. virtual tipo method() = 0;
* override: para indicar la sobreescritura de la clase base.
*/

class GameObject{
protected:
	// Atributos.
	Game* game;

	// Métodos.
	GameObject(Game*);
	virtual void render(SDL_Renderer* renderer)const = 0;
	virtual void update() = 0;
	virtual ~GameObject();
};

