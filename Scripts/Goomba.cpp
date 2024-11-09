#include "Goomba.h"

Goomba::Goomba(Game* game, std::istream& in) : game(game), dead(false), renderer(game->getRender())
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	dir = Point2D<float>(0,0);
	isGrounded = true;
	startMoving = false;
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



	if (Game::DEBUG) {
		Point2D<float> nectPos = pos + dir * MOVE_SPEED;
		SDL_Rect rect2 = collider;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		SDL_RenderDrawRect(renderer, &rect2);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
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

	if (!isGrounded) {
		dir = Point2D<float>(dir.GetX(), dir.GetY() + GRAVITY);
		if (dir.GetY() > MAX_FALL_SPEED) {
			dir = Point2D<float>(dir.GetX(), MAX_FALL_SPEED);
		}
	}

	// distancia del player para el start moving
	Point2D<float> playerPos ;
	Point2D<float> dis = playerPos - pos;
	if (dis.GetX() >= 10.0) {
		startMoving = true;
	}


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

	// segun la dir hay que cambiar la pos del collisionRect


	collisionResult = game->checkCollision(collisionRect, false); // TILEMAP.

	hit(collisionResult.intersectRect, collisionResult.damages);




}

Collision::collision Goomba::hit(const SDL_Rect& rect, bool fromPlayer) {
	// TILEMAP.
	if (!fromPlayer) {
		if (rect.w >= rect.h){
			if (rect.y < collisionRect.y) {
				isGrounded = true;
			}
		}
		else if(rect.h > rect.x) {
			if (dir.GetX() == MOVE_SPEED) {
				dir = Point2D<float>(-MOVE_SPEED, dir.GetY());
			}
			else if(dir.GetX() == -MOVE_SPEED){
				dir = Point2D<float>(MOVE_SPEED, dir.GetY());
			}
		}
		else {
			isGrounded = true;
		}
	}
	else {
		if (rect.w >= rect.h) {
			// elimina goomba
			delete this;
		}
	}

	Collision::collision col;
	return col;

}