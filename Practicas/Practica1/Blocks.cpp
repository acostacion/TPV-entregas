#include "Blocks.h"

Blocks::Blocks(Game* _game, std::istream& in) : game(_game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	anim = false;
	action = Accion::nada;
	tipo = Tipos::ladrillo;
	animFrame = 0;
	animTimer = 3;
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

		if (c == 'C') {
			action = Accion::moneda; // Caso "coin".
		}
		else {
			action = Accion::potenciador; // Caso "potentiator".//creo q mushroom
		}
		animFrame = 0;
		break;

	case 'H': // Si es un bloque oculto...
		tipo = Tipos::oculto;
		if (c == 'C') {
			action = Accion::moneda;
		}
		else {
			action = Accion::potenciador;
		}
		animFrame = 6;
		break;
	}

	texturaBlock = _game->getTexture(Game::BLOCKS); // obtiene la textura.

	colision.x = pos.GetX() * Game::TILE_SIDE;
	colision.y = pos.GetY() * Game::TILE_SIDE;
	colision.w = texturaBlock->getFrameWidth() * 2;
	colision.h = texturaBlock->getFrameHeight() * 2;
};

void Blocks::readBlocks(char c, std::istream& in) {
	
}

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

void Blocks::render(SDL_Renderer* renderer) {

	// si es el sorpresa
	if (animTimer == 0) {
		if (anim) {
			if (animFrame == 0) animFrame = 1;
			else if (animFrame == 1) animFrame = 2;
			else if (animFrame == 2) animFrame = 3;
			else if (animFrame == 3) animFrame = 0;
		}
	}
	
	SDL_Rect rect = createBlockRect();
	// Se renderiza.
	texturaBlock->renderFrame(rect, 0, animFrame);

	if (Game::DEBUG) {
		SDL_Rect rect2 = createBlockRect();

		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &rect2);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Blocks::changeSprite(){
   	if (tipo == Tipos::ladrillo) {
		animFrame = 5;
	}
	else if (tipo == Tipos::vacio) {
		animFrame = 4;
	}
	else if (tipo == Tipos::oculto) {
		animFrame = 6;
	}
	anim = false;
}

void Blocks::update() {
	if (animTimer >= 0) {
		animTimer--;
	}
	else {
		animTimer = 3;
	}
}

Collision::collision Blocks::hit(const SDL_Rect& other, bool fromPlayer){
	Collision::collision colBlock;
	if (!(colision.x == other.x && colision.y == other.y && colision.w == other.w && colision.h == other.h))
	{
		colBlock.collides = SDL_IntersectRect(&other, &colision, &colBlock.intersectRect);
		if (colBlock.collides) { // si hay interseccion
			/*if (!(collider.x == rect.x && collider.y == rect.y && collider.w == rect.w && collider.h == rect.h))
			{*/
			if (fromPlayer && other.y > colision.y) {
				if (other.y <= colision.y + colision.h) {
					// Se crea el rect de colision del bloque con el mismo tamaño que el del render.

					//Colisiona un rect que viene de fuera con el del bloque.


					// Si colisiona el collider del bloque con otro...
					//if (collision) colBlock = { true, false, blockRect }; // {colisiona, damage, rect interseccion}

					// IR MODIFICANDO COLBLOCK SEGUN SE NECESITE.
					if (tipo == Tipos::ladrillo) {

						if (game->getSMario()) { // MARIO Grande.
							// ladrillo se puede romper
							tipo = Tipos::vacio;
							//colBlock = { true, false, blockRect };
						}

					}
					else if (tipo == Tipos::sorpresa) {
						// Si mario siendo M o SM choca con los sorpresa.
						// O sale la seta o salen monedas, etc.
						if (action == Accion::moneda) {

						}
						else if (action == Accion::potenciador) {

							game->addMushroom(new Mushroom(game, { pos.GetX() / Game::TILE_SIDE, pos.GetY() / Game::TILE_SIDE - 1 }));
						}

						tipo = Tipos::vacio;
						changeSprite();
					}
					else if (tipo == Tipos::oculto) {
						// Si mario siendo M o SM choca con los vacios.
						// Aparece el bloque vacío (se le cambia la textura y se muestra lo que era).
						if (action == Accion::moneda) {

						}
						else if (action == Accion::potenciador) {
							game->addMushroom(new Mushroom(game, { pos.GetX() / Game::TILE_SIDE, pos.GetY() / Game::TILE_SIDE - 1 }));
						}
						tipo = Tipos::ladrillo;
						changeSprite();
					}
					else if (tipo == Tipos::vacio) {

					}
				}
			}
			colBlock.collides = true;

		}
	}
	return colBlock;

}
