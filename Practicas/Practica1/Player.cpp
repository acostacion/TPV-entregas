#include "Player.h"


Player::Player(Game* game, std::istream& in) : game(game)
{
	in >> pos; // será in Point2D que sabe leerse
	pos = pos - Point2D<float>(0, 1);
	in >> life; // el número de vidas
	dir = Point2D<float>(0,0);
	superMario = false;
	texturaMario = game->getTexture(Game::MARIO);
	texturaSMario = game->getTexture(Game::SUPERMARIO);
}


void Player::render() {
	SDL_Rect rect;
	/*/if (!this->superMario) {*/
	rect.w = texturaMario->getFrameWidth();
		rect.h = texturaMario->getFrameHeight();
		rect.x = pos.GetX() * Game::TILE_SIDE;
		rect.y = pos.GetY() * Game::TILE_SIDE;
		texturaMario->renderFrame(rect, 0, 0);
}


void Player::handleEvent(SDL_Event evento) {

	Point2D<float> nuevaDir;

	switch (evento.key.keysym.sym) {
	case SDLK_LEFT:
		nuevaDir = Point2D<float>(-1,0);
		break;
	case SDLK_RIGHT:
		nuevaDir = Point2D<float>(1, 0);
		break;
	case SDLK_UP:
		nuevaDir = Point2D<float>(0, -1);
		break;
	case SDLK_DOWN:
		nuevaDir = Point2D<float>(0, 1);
		break;
	default:
		break;
	}
	dir = nuevaDir * 2;
	pos = pos + dir;


}