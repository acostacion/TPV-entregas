#include "Blocks.h"

Blocks::Blocks(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	texturaBlock = game->getTexture(Game::BLOCKS);
	char c;
	in >> c;
	switch (c) {
	case 'B':
		tp = Tipos::ladrillo;
		ac = Accion::nada;
		break;
	case '?':
		tp = Tipos::sorpresa;
		in >> c;
		if ( c == 'C') ac = Accion::moneda;
		else ac = Accion::potenciador;
		break;
	case 'H':
		tp = Tipos::oculto;
		if (c == 'C') ac = Accion::moneda;
		else ac = Accion::potenciador;
		break;
	}
}

void Blocks::render() {

	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posici�n.
	rect.w = texturaBlock->getFrameWidth() *2;
	rect.h = texturaBlock->getFrameHeight()*2 ;
	rect.x = pos.GetX() * Game::TILE_SIDE;
	rect.y = pos.GetY() * Game::TILE_SIDE;

	int fx = 0;
	switch (tp) {
	case Tipos::ladrillo:
		fx = 5;
		break;
	case Tipos::sorpresa:
		fx = 0;
		break;
	case Tipos::oculto:
		fx = 5;
		break;
	case Tipos::vacio:
		fx = 4;
		break;

	}

	// Se renderiza.
	texturaBlock->renderFrame(rect, fx, 0);
}


void Blocks::update() {

}