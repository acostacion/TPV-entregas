#include "Goomba.h"

Goomba::Goomba(Game* game, std::istream& in) : game(game), dead(false)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	dir = Point2D<float>(-1,0);

	isGrounded = true;
	frozen = true;
	timer = 3;
	anim = 0;
    texturaGoomba = game->getTexture(Game::GOOMBA);
	collisionRect = createRect(
		pos.GetX() * Game::TILE_SIDE,
		pos.GetY() * Game::TILE_SIDE);
}
SDL_Rect Goomba::createRect(float x, float y) {
	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posición.
	rect.w = texturaGoomba->getFrameWidth() *2;
	rect.h = texturaGoomba->getFrameHeight()*2;
	rect.x = x;
	rect.y = y;

	return rect;
}

void Goomba::render(SDL_Renderer* renderer) {
	
	// 1. Se crea el rect.
	SDL_Rect rect = createRect(
		pos.GetX() * Game::TILE_SIDE - game->getMapOffset(),
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



	if (Game::DEBUG) {
		Point2D<float> nextPos = pos + dir * MOVE_SPEED;
		SDL_Rect rect2 = createRect((nextPos.GetX() * Game::TILE_SIDE) - game->getMapOffset(), nextPos.GetY() * Game::TILE_SIDE);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		SDL_RenderDrawRect(renderer, &rect2);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}




void Goomba::update() {

	if(pos.GetX() * Game::TILE_SIDE < game->getMapOffset() + Game::WIN_WIDTH)
		frozen = false;


	if (timer >= 0) {
		timer--;
	}
	else {
		timer = 3;
	}

    if (!frozen) {
		Point2D<float> nextPos = pos + dir * MOVE_SPEED;

		SDL_Rect nextCollider = createRect(nextPos.GetX() * Game::TILE_SIDE, nextPos.GetY() * Game::TILE_SIDE);
		Collision::collision result = game->checkCollision(nextCollider, false);

		if (!result.collides) {
			pos = nextPos;
		}
		else {
			
			if (result.intersectRect.h <= MARGIN_Y && result.intersectRect.w <= MARGIN_X) {
				pos = nextPos;
			}
			else {
				//invertir la direccion
				dir.SetX(-dir.GetX());
			}
			
		}

		//si atraviesa el borde izquierdo del mapa o cae por su parte inferior
		if (pos.GetX() * Game::TILE_SIDE < game->getMapOffset() || pos.GetY() > Game::WIN_HEIGHT) {
			dead = true;
		}

    }

}

Collision::collision Goomba::hit(const SDL_Rect& other, bool fromPlayer) {
	// collides, damages, intersectrect.
	Collision::collision colGoomba;
	SDL_Rect col = createRect(pos.GetX() * Game::TILE_SIDE, pos.GetY() * Game::TILE_SIDE);

	//Colisiona un rect que viene de fuera con el del goomba.

	if(fromPlayer) {
		colGoomba.collides = SDL_IntersectRect(&col, &other, &colGoomba.intersectRect);
		if (colGoomba.collides) {
			if (colGoomba.intersectRect.w > col.w / 4 && game->getPlayerDirectionY() == 1)
				dead = true;
			else if (colGoomba.intersectRect.h > col.h / 2 && !colGoomba.fromSuperMario) colGoomba.damages = true;
			else colGoomba.fromEnemy = true;
		}
	}
	return colGoomba;
}