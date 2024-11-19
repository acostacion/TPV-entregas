#include "CheckML.h"
#include "Mushroom.h"
#include "Game.h"

Mushroom::Mushroom(Game* _game, const Point2D<float>& _pos): Pickable(_game, _pos){
	textura = game->getTexture(Game::MUSHROOM);
}


void Mushroom::render(SDL_Renderer* renderer) const{
	// 1. Se crea el rect.
	// 2. Se le da dimensiones y posici�n.
	SDL_Rect rect = createRect(pos.GetX() * Game::TILE_SIDE - game->getMapOffset(), pos.GetY() * Game::TILE_SIDE);

	textura->renderFrame(rect, 0, 0);

	if (Game::DEBUG) {
		Point2D<float> nextPos = pos + dir * moveSpeed;
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
	Collision result = game->checkCollision(nextCollider, false);

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

