#include "Mushroom.h"


Mushroom::Mushroom(Game* _game, const Point2D<float>& _pos) {
	game = _game;
	pos = {_pos.GetX(), _pos.GetY() - 1};
	std::cout << pos.GetX() << " " << pos.GetY();
	dir = Point2D<float>(1, 0);
	dead = false;
	texturaMushroom = game->getTexture(Game::MUSHROOM);
}


SDL_Rect
Mushroom::createRect(int x, int y) const {
	return { x, y, texturaMushroom->getFrameWidth() * 2, texturaMushroom->getFrameHeight() * 2 };
}


void Mushroom::render(SDL_Renderer* renderer) {
	// 1. Se crea el rect.
	// 2. Se le da dimensiones y posici�n.
	SDL_Rect rect = createRect((pos.GetX() * Game::TILE_SIDE ) - game->getMapOffset(), pos.GetY() * Game::TILE_SIDE);

	texturaMushroom->renderFrame(rect, 0, 0);

	if (Game::DEBUG) {
		Point2D<float> nextPos = pos + dir * MOVE_SPEED;
		SDL_Rect rect2 = createRect((
			nextPos.GetX() * Game::TILE_SIDE) - game->getMapOffset(), nextPos.GetY()* Game::TILE_SIDE);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		SDL_RenderDrawRect(renderer, &rect2);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Mushroom::update() {
	// Calcular la próxima posicion basada en la direccion y velocidad de movimiento
	Point2D<float> nextPos = pos + Vector2D<float>(dir.GetX() * (MOVE_SPEED_X - FALL_OFFSET), MOVE_SPEED_Y);
	SDL_Rect nextCollider = createRect(nextPos.GetX() * Game::TILE_SIDE, nextPos.GetY() * Game::TILE_SIDE);
	Collision::collision result = game->checkCollision(nextCollider, false);

	if (!result.collides) {
		pos = nextPos;
	}
	else {
		nextPos = pos + Vector2D<float>(dir.GetX() * MOVE_SPEED_X, dir.GetY() * MOVE_SPEED_Y);
		SDL_Rect nextCollider = createRect(nextPos.GetX() * Game::TILE_SIDE, nextPos.GetY() * Game::TILE_SIDE);
		Collision::collision result = game->checkCollision(nextCollider, false);
		if (!result.collides) {
			pos = nextPos;
		}
		else {
			if (result.intersectRect.h <= MARGENY && result.intersectRect.w <= MARGENX) {
				pos = nextPos;
			}
			else {
				//invertir la direccion
				dir.SetX(-dir.GetX());
			}
		}
	}
}

Collision::collision Mushroom::hit(const SDL_Rect& other, bool fromPlayer) {
	Collision::collision res;
	SDL_Rect rect = createRect(pos.GetX() * Game::TILE_SIDE, pos.GetY() * Game::TILE_SIDE);
	if(SDL_IntersectRect(&other, &rect, &res.intersectRect)) {
		res.collides = true;
		if (fromPlayer) { // se elimina y cambia el player
			dead = true;
			res.fromMushroom = true;
		}
	}
	
	return res;
}