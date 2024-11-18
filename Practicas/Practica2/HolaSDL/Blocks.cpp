#include "CheckML.h"
#include "Blocks.h"

Blocks::Blocks(Game* _game, std::istream& in) 
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	action = Action::nada;
	tipo = Variant::ladrillo;

	char c;
	in >> c;
	switch (c) {
	case 'B': // Si es un bloque ladrillo... 
		tipo = Variant::ladrillo;
		action = Action::nada;
		animFrame = 5;
		break;

	case '?': // Si es un bloque "?"...
		tipo = Variant::sorpresa;
		in >> c;
		anim = true;

		// c true -> action es moneda : c false -> action es potenciador
		action = (c == 'C') ? Action::moneda : Action::potenciador;

		animFrame = 0;
		break;

	case 'H': // Si es un bloque oculto...
		tipo = Variant::oculto;
		action = (c == 'C') ? Action::moneda : Action::potenciador;
		animFrame = 6;
		break;
	}

	textura = _game->getTexture(Game::BLOCKS); // obtiene la textura.
};



void Blocks::render(SDL_Renderer* renderer) {

	// si es el sorpresa
	if (timer == 0 && anim) {
		
		if (animFrame == 0) animFrame = 1;
		else if (animFrame == 1) animFrame = 2;
		else if (animFrame == 2) animFrame = 3;
		else if (animFrame == 3) animFrame = 0;	
	}
	
	SDL_Rect rect = createRect(pos.GetX(), pos.GetY());
	textura->renderFrame(rect, 0, animFrame); // Se renderiza.

	if (Game::DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Blocks::changeSprite(){
   	if (tipo == Variant::ladrillo) {
		animFrame = 5;
	}
	else if (tipo == Variant::vacio) {
		animFrame = 4;
	}
	else if (tipo == Variant::oculto) {
		animFrame = 6;
	}
	anim = false; // Si cambian de tipo detiene animacion.
}

void Blocks::update() {
	// Va decrementando el temporizador si esta activo y lo reinicia al llegar 
	if (timer >= 0) {
		timer--;
	}
	else {
		timer = 3;
	}
}

// RUBÉN LUEGO DARÁ LAS COLISIONES HECHAS.
Collision::collision Blocks::hit(const SDL_Rect& other, bool fromPlayer){
	Collision::collision colBlock;
	SDL_Rect colision = createRect(pos.GetX(), pos.GetY());
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
					if (tipo == Variant::ladrillo) {

						if (game->getSMario()) { // MARIO Grande.
							// ladrillo se puede romper
							//colBlock = { true, false, blockRect };
							destroyed = true;

						}

					}
					else if (tipo == Variant::sorpresa) {
						// Si mario siendo M o SM choca con los sorpresa.
						// O sale la seta o salen monedas, etc.
						if (action == Action::moneda) {

						}
						else if (action == Action::potenciador) {

							game->addMushroom(new Mushroom(game, { pos.GetX() , pos.GetY()  - Game::TILE_SIDE }));
						}

						tipo = Variant::vacio;
						changeSprite();
					}
					else if (tipo == Variant::oculto) {
						// Si mario siendo M o SM choca con los vacios.
						// Aparece el bloque vacío (se le cambia la textura y se muestra lo que era).
						if (action == Action::moneda) {

						}
						else if (action == Action::potenciador) {
							game->addMushroom(new Mushroom(game, { pos.GetX(), pos.GetY() - Game::TILE_SIDE }));
						}
						tipo = Variant::vacio;
						changeSprite();
					}
					else if (tipo == Variant::vacio) {

					}
				}
			}
			colBlock.collides = true;

		}
	}
	return colBlock;

}
