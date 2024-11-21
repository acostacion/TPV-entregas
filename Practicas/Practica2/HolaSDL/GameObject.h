#pragma once
#include <SDL.h>

/*
* virtual: para indicar que un método se puede sobreescribir por subclases. virtual tipo method() = 0;
* override: para indicar la sobreescritura de la clase base.
*/

class Game;

class GameObject{
protected:
	// Atributos.
	Game* game = nullptr;

public:
	// Constructoras y Destructoras.
	GameObject() = default; // Constructora default.
	GameObject(Game* _game) { game = _game; } // Constructora con "game".
	virtual ~GameObject() = default; // Destructora default.

	// Métodos virtuales puros (las subclases los reescribirán).
	virtual void render()const = 0;
	virtual void update() = 0;

	// Getters.
	virtual Game* getGame() { return game; }
};

