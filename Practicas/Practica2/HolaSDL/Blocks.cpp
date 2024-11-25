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
	colision.x = pos.GetX() * TILE_SIDE;
	colision.y = pos.GetY() * TILE_SIDE;
	colision.w = width;
	colision.h = height;
};

void Blocks::render(SDL_Renderer* renderer) {

	updateAnimation();
	
	SDL_Rect rect = createBlockRect();
	texture->renderFrame(rect, 0, animFrame); // Se renderiza.

	if (DEBUG) {
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

Collision Blocks::hit(const SDL_Rect& region, Collision::Target target)
{
	// Calcula la intersección
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	if (hasIntersection) {
		Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };

		// LÓGICA DE EFECTOS DE BLOQUE.

		return collision;
	}

	return NO_COLLISION;
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
	rect.x = pos.GetX() * TILE_SIDE - game->getMapOffset();
	rect.y = pos.GetY() * TILE_SIDE;

	return rect;
}
#pragma endregion