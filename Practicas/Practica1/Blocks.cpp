#include "Blocks.h"

Blocks::Blocks(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	texturaBlock = game->getTexture(Game::BLOCKS);
	anim = false;
	ac = Accion::nada;
	tp = Tipos::ladrillo;
	fx = 0;
	char c;
	in >> c;
	switch (c) {
	case 'B':
		tp = Tipos::ladrillo;
		ac = Accion::nada;
		fx = 5;
		break;
	case '?':
		tp = Tipos::sorpresa;
		in >> c;
		anim = true;
		if ( c == 'C') ac = Accion::moneda;
		else ac = Accion::potenciador;
		fx = 0;
		break;
	case 'H':
		tp = Tipos::oculto;
		if (c == 'C') ac = Accion::moneda;
		else ac = Accion::potenciador;
		fx = 5;
		break;
	}
}

void Blocks::render() {

	// 1. Se crea el rect.
	SDL_Rect rect;


	// 2. Se le da dimensiones y posici�n.
	rect.w = texturaBlock->getFrameWidth() *2;
	rect.h = texturaBlock->getFrameHeight() *2;
	rect.x = pos.GetX() * Game::TILE_SIDE - game->getMapOffset();
	rect.y = pos.GetY() * Game::TILE_SIDE;

	if (anim) {
		if (fx == 0) fx = 1;
		else if (fx == 1) fx = 2;
		else if (fx == 2) fx = 3;
		else if (fx == 3) fx = 0;
	}


	// Se renderiza.
	texturaBlock->renderFrame(rect, 0, fx);
}


void Blocks::update() {
	
}