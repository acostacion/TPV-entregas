#include "checkML.h"
#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* _game, std::istream& in) 
	: SceneObject(_game, pos, width, height, texture), game(_game){
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
}

void Enemy::render(SDL_Renderer* renderer) {
	SDL_Rect rect = createRect(pos.GetX() * Game::TILE_SIDE, pos.GetY() * Game::TILE_SIDE);

	if (anim == 0) anim = 1;
	else anim = 0;

	texture->renderFrame(rect, 0, anim);

	if (Game::DEBUG) {
		Point2D<float> nextPos = pos + dir * MOVE_SPEED;
		SDL_Rect rect2 = createRect((nextPos.GetX() * Game::TILE_SIDE) - game->getMapOffset(), nextPos.GetY() * Game::TILE_SIDE);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		SDL_RenderDrawRect(renderer, &rect2);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Enemy::update() {

	// Verificar si el personaje está dentro de la pantalla para activar movimiento
	bool isOnScreen = (pos.GetX() * Game::TILE_SIDE > game->getMapOffset()) &&
		(pos.GetX() * Game::TILE_SIDE < game->getMapOffset() + Game::WIN_WIDTH);

	if (isOnScreen) {
		frozen = false;
	}

	// Si no está congelado, procede a moverse
	if (!frozen) {

		if (timer >= 0) {
			timer--;
		}
		else {
			timer = 3;
		}

		// Intentar moverse en Y hacia abajo
		Point2D<float> nextPos = pos + Vector2D<float>(0, 1) * MOVE_SPEED;
		SDL_Rect nextCollider = createRect(nextPos.GetX() * Game::TILE_SIDE, nextPos.GetY() * Game::TILE_SIDE);
		Collision::collision result = game->checkCollision(nextCollider, false);

		if (!result.collides) {// Sin colisión en Y, actualizar posición
			pos = nextPos;
		}
		else {
			nextPos = pos + dir * MOVE_SPEED;
			nextCollider = createRect(nextPos.GetX() * Game::TILE_SIDE, nextPos.GetY() * Game::TILE_SIDE);
			result = game->checkCollision(nextCollider, false);
			if (!result.collides) pos = nextPos;// Sin colisión en X, actualizar posición
			else if (result.intersectRect.h <= MARGIN_Y && result.intersectRect.w <= MARGIN_X) pos = nextPos;// Si la colisión está dentro de los márgenes, actualizar posición
			else {
				// Si la colisión excede los márgenes, invertir la dirección
				dir.SetX(-dir.GetX());
			}
		}

		//si atraviesa el borde izquierdo del mapa o cae por su parte inferior
		if (pos.GetX() * Game::TILE_SIDE < game->getMapOffset() || pos.GetY()>Game::WIN_HEIGHT) {
			dead = true;
		}

	}
}

Collision::collision Enemy::hit(const SDL_Rect& other, bool fromPlayer) {
	// collides, damages, intersectrect.
	Collision::collision colGoomba;
	SDL_Rect col = createRect(pos.GetX() * Game::TILE_SIDE, pos.GetY() * Game::TILE_SIDE);

	//Colisiona un rect que viene de fuera con el del goomba.
	if (fromPlayer) {
		colGoomba.collides = SDL_IntersectRect(&col, &other, &colGoomba.intersectRect);
		if (colGoomba.collides) {
			if (other.y < col.y) // si viene por arriba
				dead = true;
			else {
				colGoomba.damages = true;
				colGoomba.fromEnemy = true;
			}
		}
	}

	return colGoomba;
}

#pragma region Submétodos
SDL_Rect Enemy::createRect(float x, float y) {
	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posición.
	rect.w = texture->getFrameWidth() * 2;
	rect.h = texture->getFrameHeight() * 2;
	rect.x = x;
	rect.y = y;

	return rect;
}
#pragma endregion

