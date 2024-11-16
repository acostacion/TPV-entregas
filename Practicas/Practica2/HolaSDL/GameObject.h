#pragma once
#include "Game.h"
#include <SDL.h>

/*
* virtual: para indicar que un método se puede sobreescribir por subclases. virtual tipo method() = 0;
* override: para indicar la sobreescritura de la clase base.
*/

class GameObject
{
protected:
	Game* game;
public:
	GameObject(Game* gameInstance) {
		game = gameInstance;
	}
	// LUEGO HAY QUE HACER RENDER CONST.
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void update() = 0;
	virtual ~GameObject();
};

