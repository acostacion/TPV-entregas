#include "Goomba.h"

Goomba::Goomba(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	dir = Point2D<float>(0,0);
    startMoving = true;
	dead = false;
	anim = 0;
    texturaGoomba = game->getTexture(Game::GOOMBA);
}

void Goomba::render() {
	
	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posición.
	rect.w = texturaGoomba->getFrameWidth() * 2;
	rect.h = texturaGoomba->getFrameHeight() * 2;
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
    texturaGoomba->renderFrame(rect, 0, anim);
}


void Goomba::update() {

    if (startMoving) {
		dir = Point2D<float>(-MOVE_SPEED, 0);
    }
	pos = pos + dir;

}

void Goomba::hit() {

}