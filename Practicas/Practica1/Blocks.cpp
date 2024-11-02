#include "Blocks.h"

Blocks::Blocks(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	texturaBlock = game->getTexture(Game::BLOCKS); // obtiene la textura.
	anim = false; 
	action = Accion::nada;
	tipo = Tipos::ladrillo;
	animFrame = 0;
	timer = 3;

	// Lee el tipo del txt.
	char c;
	in >> c;
	switch (c) {
	case 'B': // Si es un bloque ladrillo... 
		tipo = Tipos::ladrillo;
		action = Accion::nada;
		animFrame = 5;
		break;

	case '?': // Si es un bloque "?"...
		tipo = Tipos::sorpresa;
		in >> c;
		anim = true;

		if ( c == 'C') action = Accion::moneda; // Caso "coin".
		else action = Accion::potenciador; // Caso "potentiator".
		animFrame = 0;
		break;

		// Si es un bloque oculto...
	case 'H':
		tipo = Tipos::oculto;
		if (c == 'C') action = Accion::moneda;
		else action = Accion::potenciador;
		animFrame = 5;
		break;
	}
}

void Blocks::render() {

	// si es el sorpresa
	if (timer == 0) {
		if (anim) {
			if (animFrame == 0) animFrame = 1;
			else if (animFrame == 1) animFrame = 2;
			else if (animFrame == 2) animFrame = 3;
			else if (animFrame == 3) animFrame = 0;
		}
	}

	// Se renderiza.
	texturaBlock->renderFrame(createBlockRect(), 0, animFrame);
}

// Submétodos.
SDL_Rect Blocks::createBlockRect() {

	// 1. Se crea el rect.
	SDL_Rect rect;


	// 2. Se le da dimensiones y posici�n.
	rect.w = texturaBlock->getFrameWidth() * 2;
	rect.h = texturaBlock->getFrameHeight() * 2;
	rect.x = pos.GetX() * Game::TILE_SIDE - game->getMapOffset();
	rect.y = pos.GetY() * Game::TILE_SIDE;

	return rect;
}


void Blocks::update() {
	if (timer >= 0) {
		timer--;
	}
	else {
		timer = 3;
	}
}

Collision Blocks::hit(const SDL_Rect& rect, bool fromPlayer) {

	/*// Se crea el rect de colision del bloque con el mismo tamaño que el del render.
	SDL_Rect blockRect = createBlockRect();

	// Colisiona un rect que viene de fuera con el del bloque.
	SDL_bool collision = SDL_HasIntersection(&blockRect, otherRect)

		/*
	if (tipo == Tipos::ladrillo) {
		// Si mario choca con los ladrillos siendo M.
		if()
		// Si mario choca con los ladrillos siendo SM.
	}
	else if (tipo == Tipos::sorpresa) {
		// Si mario choca con los sorpresa siendo M.
		// Si mario choca con los sorpresa siendo SM.
	}
	else if (tipo == Tipos::vacio) {
		// Si mario siendo M o SM choca con los vacios.
	}*/
	return { true, true };
}
