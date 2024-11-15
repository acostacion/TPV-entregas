#pragma once
#include "Game.h"
#include <SDL.h>

/*
* virtual: para indicar que un método se puede sobreescribir por subclases.
* override: para indicar la sobreescritura de la clase base.
*/

class GameObject
{
private:
	Game* game;
public:
	GameObject(Game* gameInstance) {
		game = gameInstance;
	}
	virtual void render()const;
	virtual void update();
	virtual ~GameObject();
};

