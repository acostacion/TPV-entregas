#include "Goomba.h"

Goomba::Goomba(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	dir = Point2D<float>(0,0);
    startMoving = true;
	dead = false;
	timer = 3;
	anim = 0;
    texturaGoomba = game->getTexture(Game::GOOMBA);
	collisionRect = createRect(texturaGoomba->getFrameWidth() * 2,
		texturaGoomba->getFrameHeight() * 2,
		pos.GetX() * Game::TILE_SIDE,
		pos.GetY() * Game::TILE_SIDE);
}

void Goomba::render() {
	
	// 1. Se crea el rect.
	SDL_Rect rect = createRect(texturaGoomba->getFrameWidth() * 2,
		texturaGoomba->getFrameHeight() * 2,
		pos.GetX() * Game::TILE_SIDE,
		pos.GetY() * Game::TILE_SIDE);

	// 3. Frame de la animacion
	if (dead) {
		anim = 2;
	}

	if (timer == 0 && !dead) {
		if (anim == 0) anim = 1;
		else anim = 0;
	}
	
	

	// Se renderiza.
    texturaGoomba->renderFrame(rect, 0, anim);
}

SDL_Rect Goomba::createRect(int w, int h, int x, int y) {
	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posición.
	rect.w = w;
	rect.h = h;
	rect.x = x;
	rect.y = y;

	return rect;
}


void Goomba::update() {
	if (timer >= 0) {
		timer--;
	}
	else {
		timer = 3;
	}

    if (startMoving) {
		dir = Point2D<float>(-MOVE_SPEED, 0);
    }
	pos = pos + dir;

	collisionResult = game->checkCollision(collisionRect, false); // TILEMAP.
	
}

Collision Goomba::hit(const SDL_Rect& rect, bool fromPlayer) {
	// TILEMAP.
	if (collisionResult = {true, false, })
}