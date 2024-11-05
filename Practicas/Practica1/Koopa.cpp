#include "Koopa.h"

Koopa::Koopa(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	dir = Point2D<float>(0,0);
    startMoving = true;
	dead = false;
	anim = 0;
	texturaKoopa = game->getTexture(Game::KOOPA);
}

void Koopa::render() {
	
	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posici�n.
	rect.w = texturaKoopa->getFrameWidth() * 2;
	rect.h = texturaKoopa->getFrameHeight() * 2;
	rect.x = pos.GetX() * Game::TILE_SIDE;
	rect.y = pos.GetY() * Game::TILE_SIDE;

	// 3. Frame de la animacion
	if (dead) {
		anim = 2;
	}
	else {
		if (anim == 0) anim = 1;
		else anim = 0;
	}

	// Se renderiza.
	texturaKoopa->renderFrame(rect, 0, anim);

	if (Game::DEBUG) {
		Point2D<float> nectPos = pos + dir * MOVE_SPEED;
		SDL_Rect rect2 = collider;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		SDL_RenderDrawRect(renderer, &rect2);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}


void Koopa::update() {

    if (startMoving) {
		dir = Point2D<float>(-MOVE_SPEED, 0);
    }
	pos = pos + dir;
}

Collision Koopa::hit(const SDL_Rect& rect, bool fromPlayer) {
	
}