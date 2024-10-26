#include "Player.h"


Player::Player(Game* game, std::istream& in) : game(game)
{
	in >> pos; // Lee la posición inicial.
	pos = pos - Point2D<float>(0, 1); // Ajusta la pos.

	in >> life; // Lee el número de vidas.

	dir = Point2D<float>(0,0); 

	superMario = false; 

	// Pilla las texturas del game.
	texturaMario = game->getTexture(Game::MARIO);
	texturaSMario = game->getTexture(Game::SUPERMARIO);
}

void Player::render() {
	
	/*/if (!this->superMario) {*/

	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posición.
	rect.w = texturaMario->getFrameWidth();
	rect.h = texturaMario->getFrameHeight();
	rect.x = pos.GetX() * Game::TILE_SIDE;
	rect.y = pos.GetY() * Game::TILE_SIDE;

	// Se renderiza.
	texturaMario->renderFrame(rect, 0, 0);
}

// Input de teclado cambian la dir del jugador.
void Player::handleEvent(SDL_Event evento) {

	Point2D<float> nuevaDir;

	SDL_Scancode tecla = evento.key.keysym.scancode;

	if (tecla) {
		if (evento.type == SDLK_LEFT || evento.type == SDLK_a) {
			nuevaDir = Point2D<float>(-1, 0);
		}
		else if (evento.type == SDLK_RIGHT || evento.type == SDLK_d) {
			nuevaDir = Point2D<float>(1, 0);
		}
		else if (evento.type == SDLK_UP || evento.type == SDLK_SPACE || evento.type == SDLK_w) {
			nuevaDir = Point2D<float>(0, -1);
		}
		else if (evento.type == SDLK_DOWN || evento.type == SDLK_s) {
			nuevaDir = Point2D<float>(0, 1);
		}
		else {
			nuevaDir = Point2D<float>(0, 0);
		}
	}
	// En base a la tecla presionada...
	
	
	dir = nuevaDir * 2;
}

void Player::update() { // PENDIENTE DE MODIFICAR.

	if (dir.GetX() == -1) {
		pos = pos + dir;
	}
	else if (dir.GetX() == 1) {
		pos = pos + dir;
	}
	else if (dir.GetY() == -1) {
		pos = pos + dir;
	}
	else if (dir.GetY() == 1) {
		pos = pos + dir;
	}
	
}