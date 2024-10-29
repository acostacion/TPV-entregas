#include "Blocks.h"

Blocks::Blocks(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	texturaBlock = game->getTexture(Game::BLOCKS); // obtiene la textura.
	anim = false; 
	action = Accion::nada;
	tipo = Tipos::ladrillo;
	fx = 0;
	timer = 3;

	// Lee el tipo del txt.
	char c;
	in >> c;
	switch (c) {
	case 'B': // Si es un bloque ladrillo... 
		tipo = Tipos::ladrillo;
		action = Accion::nada;
		fx = 5;
		break;

	case '?': // Si es un bloque "?"...
		tipo = Tipos::sorpresa;
		in >> c;
		anim = true;

		if ( c == 'C') action = Accion::moneda; // Caso "coin".
		else action = Accion::potenciador; // Caso "potentiator".
		fx = 0;
		break;

		// Si es un bloque oculto...
	case 'H':
		tipo = Tipos::oculto;
		if (c == 'C') action = Accion::moneda;
		else action = Accion::potenciador;
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

	// si es el sorpresa
	if (timer == 0) {
		if (anim) {
			if (fx == 0) fx = 1;
			else if (fx == 1) fx = 2;
			else if (fx == 2) fx = 3;
			else if (fx == 3) fx = 0;
		}
	}
	


	// Se renderiza.
	texturaBlock->renderFrame(rect, 0, fx);
}


void Blocks::update() {
	if (timer >= 0) {
		timer--;
	}
	else {
		timer = 3;
	}
}