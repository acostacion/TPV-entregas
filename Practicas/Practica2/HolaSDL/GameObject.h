#pragma once
#include "CheckML.h"
#include <SDL.h>

/*
* virtual: para indicar que un m�todo se puede sobreescribir por subclases. virtual tipo method() = 0;
* override: para indicar la sobreescritura de la clase base.
*/

class Game;

class GameObject{
protected:
	// Atributos.
	Game* game;

	// M�todos.
	GameObject(Game*);
	virtual void render(SDL_Renderer*)const = 0;
	virtual void update() = 0;
	virtual ~GameObject();
};

