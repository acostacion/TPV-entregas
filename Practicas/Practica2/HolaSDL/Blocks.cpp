#include "CheckML.h"
#include "Blocks.h"
#include "Game.h"

Blocks::Blocks(Game* _game, std::istream& in) 
	: SceneObject(_game, pos, width, height, texture)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.

	char c;
	in >> c;

	switch (c) {
	case 'B': 
		tipo = Tipos::LADRILLO;
		action = Accion::NADA;
		animFrame = 5;
		break;

	case '?': 
		tipo = Tipos::SORPRESA;
		in >> c;
		anim = true;

		// c true -> action es moneda : c false -> action es potenciador
		action = (c == 'C') ? Accion::MONEDA : Accion::POTENCIADOR;

		animFrame = 0;
		break;

	case 'H': // Si es un bloque oculto...
		tipo = Tipos::OCULTO;
		action = (c == 'C') ? Accion::MONEDA : Accion::POTENCIADOR;
		animFrame = 6;
		break;
	}

	texture = _game->getTexture(Game::BLOCKS); // obtiene la textura.
	width = texture->getFrameWidth() * 2;
	height = texture->getFrameHeight() * 2;

	// COLLISION RECT.
	colision.x = pos.GetX() * Game::TILE_SIDE;
	colision.y = pos.GetY() * Game::TILE_SIDE;
	colision.w = width;
	colision.h = height;
};

void Blocks::render(SDL_Renderer* renderer) {

	updateAnimation();
	
	SDL_Rect rect = createBlockRect();
	texture->renderFrame(rect, 0, animFrame); // Se renderiza.

	if (Game::DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Blocks::update() {
	// Va decrementando el temporizador si esta activo y lo reinicia al llegar 
	if (animTimer >= 0) {
		animTimer--;
	}
	else {
		animTimer = 3;
	}
}

Collision::collision Blocks::hit(const SDL_Rect& other, bool fromPlayer){
	Collision::collision colBlock;

	if (SDL_IntersectRect(&other, &colision, &colBlock.intersectRect)) { // si hay interseccion
		if (fromPlayer && other.y > colision.y && other.y <= colision.y + colision.h) {
			if (tipo == Tipos::LADRILLO) {
				if (game->getSMario()) { // MARIO Grande.
					destroyed = true;
				}
			}
			else if (tipo == Tipos::SORPRESA) {
				if (action == Accion::MONEDA) {
				}
				else if (action == Accion::POTENCIADOR) {
				}
				tipo = Tipos::VACIO;
				changeSprite();
			}
			else if (tipo == Tipos::OCULTO) {
				if (action == Accion::MONEDA) {
				}
				else if (action == Accion::POTENCIADOR) {
				}
				tipo = Tipos::VACIO;
				changeSprite();
			}
			else if (tipo == Tipos::VACIO) {
			}
		}
		colBlock.collides = true;
	}
	return colBlock;

}

#pragma region Submétodos
void Blocks::changeSprite() {
	if (tipo == Tipos::LADRILLO) {
		animFrame = 5;
	}
	else if (tipo == Tipos::VACIO) {
		animFrame = 4;
	}
	else if (tipo == Tipos::OCULTO) {
		animFrame = 6;
	}
	anim = false; // Si cambian de tipo detiene animacion.
}

void Blocks::updateAnimation() {
	// si es el sorpresa
	if (animTimer == 0 && anim) {

		if (animFrame == 0) animFrame = 1;
		else if (animFrame == 1) animFrame = 2;
		else if (animFrame == 2) animFrame = 3;
		else if (animFrame == 3) animFrame = 0;
	}
}

SDL_Rect Blocks::createBlockRect() {

	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posici�n.
	rect.w = width;
	rect.h = height;
	rect.x = pos.GetX() * Game::TILE_SIDE - game->getMapOffset();
	rect.y = pos.GetY() * Game::TILE_SIDE;

	return rect;
}
#pragma endregion