#include "CheckML.h"
#include "Mushroom.h"


Mushroom::Mushroom(Game* _game, const Point2D<float>& _pos) {
	game = _game;
	pos = _pos;
	dir = Point2D<float>(1, 0);
	dead = false;
	texturaMushroom = game->getTexture(Game::MUSHROOM);
}

SDL_Rect Mushroom::getRect(bool forRender) const {
	SDL_Rect rect;

	rect.x = pos.GetX() * Game::TILE_SIDE;
	rect.y = pos.GetY() * Game::TILE_SIDE;
	if (forRender) {
		rect.x = (pos.GetX() * Game::TILE_SIDE) - game->getMapOffset();
	}
	
	rect.w = texturaMushroom->getFrameWidth();
	rect.h = texturaMushroom->getFrameHeight();

	return rect;
}

SDL_Rect Mushroom::createRect(float x, float y) {
	// Se crea el rect.
	SDL_Rect rect;

	// Se le da dimensiones y posición.
	
	rect.w = texturaMushroom->getFrameWidth() * 2;
	rect.h = texturaMushroom->getFrameHeight() * 2;
	
	rect.x = x;
	rect.y = y;

	return rect;
}

void Mushroom::render(SDL_Renderer* renderer) {
	// 1. Se crea el rect.
	// 2. Se le da dimensiones y posici�n.
	SDL_Rect rect = createRect(pos.GetX() * Game::TILE_SIDE - game->getMapOffset(), pos.GetY() * Game::TILE_SIDE);

	texturaMushroom->renderFrame(rect, 0, 0);

	if (Game::DEBUG) {
		Point2D<float> nextPos = pos + dir * MOVE_SPEED;
		SDL_Rect rect2 = createRect(
			nextPos.GetX() * Game::TILE_SIDE,
			nextPos.GetY() * Game::TILE_SIDE);

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

	// Si no hay colisión, actualizar la posición y salir
	if (!result.collides) {
		pos = nextPos;
		return;
	}

	// En caso de colisión, recalcular posición sin el desplazamiento de caída
	nextPos = pos + Vector2D<float>(dir.GetX() * MOVE_SPEED_X, dir.GetY() * MOVE_SPEED_Y);
	nextCollider = createRect(nextPos.GetX() * Game::TILE_SIDE, nextPos.GetY() * Game::TILE_SIDE);
	result = game->checkCollision(nextCollider, false);

	// Si la nueva posición no genera colisión, actualizar la posición y salir
	if (!result.collides) {
		pos = nextPos;
		return;
	}

	// Si la colisión está dentro de los márgenes permitidos, actualizar la posición
	if (result.intersectRect.h <= MARGENY && result.intersectRect.w <= MARGENX) {
		pos = nextPos;
	}
	else {
		// Si no, invertir la dirección en el eje X
		dir.SetX(-dir.GetX());
	}
}

Collision::collision Mushroom::hit(const SDL_Rect& other, bool fromPlayer) {
	Collision::collision res;
	SDL_Rect rect = getRect(false);
	if(SDL_IntersectRect(&other, &rect, &res.intersectRect)) {
		res.collides = true;
		if (fromPlayer) { // se elimina y cambia el player
			dead = true;
			res.fromMushroom = true;
		}
	}
	
	return res;
}