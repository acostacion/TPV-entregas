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
		// Acelra la velocidad con la gravedad
	if (speed.getY() < SPEED_LIMIT)
		speed += {0, Game::GRAVITY};

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<> realSpeed = speed;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		speed.setX(-speed.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		speed.setY(0);

	// SceneObject::update(); // si hiciera falta
}

//Collision Enemy::hit(const SDL_Rect& other, bool fromPlayer) {
//	Collision colGoomba = NO_COLLISION; // Inicialmente no hay colision.
//	SDL_Rect col = createRect(pos.GetX() * Game::TILE_SIDE, pos.GetY() * Game::TILE_SIDE);
//
//	SDL_Rect intersection;
//	bool collides = SDL_IntersectRect(&col, &other, &intersection);
//	
//	if (fromPlayer) {
//		if (collides) {
//			if (other.y < col.y) // si viene por arriba
//				dead = true;
//			else {
//				colGoomba.result = Collision::DAMAGE;
//			}
//		}
//	}
//
//	return colGoomba;
//}

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

