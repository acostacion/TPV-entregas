#include "Player.h"


Player::Player(Game* game, std::istream& in) : game(game)
{
	in >> pos; // será in Point2D que sabe leerse
	in >> life; // el número de vidas
	dir = Point2D<float>(0,0);
	superMario = false;
	texturaMario = game->getTexture(Game::MARIO);
	texturaSMario = game->getTexture(Game::SUPERMARIO);
}


void Player::render() {
	SDL_Rect rect;
	if (!superMario){
		rect.w = Game::TILE_SIDE;
		rect.h = Game::TILE_SIDE;
		rect.x = pos.GetX();
		rect.y = pos.GetY();
		texturaMario->renderFrame(rect, 1, 1);

	}
	else {
		rect.w = Game::TILE_SIDE;
		rect.h = Game::TILE_SIDE * 2;
	}
	
}
