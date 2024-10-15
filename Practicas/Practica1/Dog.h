#ifndef DOG_H
#define DOG_H

#include "Texture.h"

// Declaración anticipada
class Game;

//
// Perro que se va moviendo por la ventana
//
class Dog
{
	Game* game;
	Texture* texture;
	int x, y, dx, dy;

public:

	Dog(Game* game, int x, int y);

	void update();
	void render() const;
	void handleEvent(const SDL_Event& event);
};

#endif // DOG_H
