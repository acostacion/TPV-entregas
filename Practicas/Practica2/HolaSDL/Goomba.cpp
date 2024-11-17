#include "CheckML.h"
#include "Goomba.h"

Goomba::Goomba(Game* game, std::istream& in) : Enemy(game), dead(false)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	dir = Point2D<float>(-1,0);

	isGrounded = true;
	frozen = true;
	timer = 3;
	anim = 0;
    texturaGoomba = game->getTexture(Game::GOOMBA);
}

