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

	if (timer == 0 && !dead) {
		if (anim == 0) anim = 1;
		else anim = 0;
	}
	
	

	// Se renderiza.
    texturaGoomba->renderFrame(rect, 0, anim);
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

<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> parent of dbb20b5 (Merge branch 'main' of https://github.com/acostacion/TPV-entregas)
=======
>>>>>>> parent of dbb20b5 (Merge branch 'main' of https://github.com/acostacion/TPV-entregas)
}

Collision Goomba::hit(const SDL_Rect& rect, bool fromPlayer) {
	return { true, true };
}