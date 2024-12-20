#include "Blocks.h"

Blocks::Blocks(Game* _game, std::istream& in) : game(_game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	anim = false;
	action = Accion::nada;
	tipo = Tipos::ladrillo;
	animFrame = 0;
	destroyed = false;
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
		if (colBlock.collides && other.y > colision.y && other.y <= colision.y + colision.h) { // si hay interseccion
			
			if (fromPlayer) {
				// Se crea el rect de colision del bloque con el mismo tamaño que el del render.
				if (tipo == Tipos::sorpresa || tipo == Tipos::oculto){
					// Si mario siendo M o SM choca con los sorpresa.
					// O sale la seta o salen monedas, etc.

					if (action == Accion::potenciador) {
						Point2D<float> Spawn = { (float)(colision.x / Game::TILE_SIDE), (float)(colision.y / Game::TILE_SIDE - 1) };
						game->addMushroom(new Mushroom(game, Spawn));
					}
					else if (action == Accion::moneda) {
						Point2D<float> Spawn = { (float)(colision.x / Game::TILE_SIDE), (float)(colision.y / Game::TILE_SIDE - 1) };

					}
					tipo = Tipos::vacio;
					changeSprite();
				}

				//Colisiona un rect que viene de fuera con el del bloque.
				// Si colisiona el collider del bloque con otro...
				// IR MODIFICANDO COLBLOCK SEGUN SE NECESITE.
				
				if (tipo == Tipos::ladrillo) {
					if (game->getSMario()) { // MARIO Grande.
						// ladrillo se puede romper
 						destroyed = true;
					}
				}
				
			}
			colBlock.collides = true;

		}
	}
	return colBlock;

}
