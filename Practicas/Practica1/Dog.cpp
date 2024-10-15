#include "Dog.h"
#include "Game.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

Dog::Dog(Game* game, int x, int y)
  : game(game)
  , texture(game->getTexture(Game::DOG))
  , x(x)
  , y(y)
  , dx(SPEED)
  , dy(0)
{
}

#include <iostream>

void
Dog::update()
{
	// Hace que el perro avance y vuelva a aparecer por la izquierda
	if ((x += dx) >= int(Game::WIN_WIDTH))
		x = -texture->getFrameWidth();
}

void
Dog::render() const
{
	SDL_Rect destino{x, y, texture->getFrameWidth(), texture->getFrameHeight()};
	texture->renderFrame(destino, 0, (abs(x) / FRAME_PERIOD) % texture->getNumColumns());
}

void
Dog::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d) {
		dx = dx != 0 ? 0 : SPEED;
	}
}
