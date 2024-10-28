#include "Blocks.h"

Blocks::Blocks(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.

    texturaGoomba = game->getTexture(Game::GOOMBA);
}

void Blocks::render() {
	
	/*/if (!this->superMario) {*/

	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posici�n.
	rect.w = texturaGoomba->getFrameWidth() * 2;
	rect.h = texturaGoomba->getFrameHeight() * 2;
	rect.x = pos.GetX() * Game::TILE_SIDE;
	rect.y = pos.GetY() * Game::TILE_SIDE;

	// Se renderiza.
    texturaGoomba->renderFrame(rect, 0, 0);
}


void Blocks::update() {

    

}