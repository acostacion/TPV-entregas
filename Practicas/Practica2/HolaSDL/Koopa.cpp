#include "CheckML.h"
#include "Koopa.h"

Koopa::Koopa(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	dir = Point2D<float>(0,0);
	isGrounded = true;
	frozen = true;
	timer = 3;
	anim = 0;
	texturaKoopa = game->getTexture(Game::KOOPA);
}
SDL_Rect Koopa::createRect(float x, float y) {
	//1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posición.
	rect.w = texturaKoopa->getFrameWidth() * 2;
	rect.h = texturaKoopa->getFrameHeight() * 2;
	rect.x = x;
	rect.y = y;

	return rect;
}
void Koopa::render(SDL_Renderer* renderer) {
	
	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posici�n.
	rect.w = texturaKoopa->getFrameWidth() * 2;
	rect.h = texturaKoopa->getFrameHeight() * 2;
	rect.x = pos.GetX() * Game::TILE_SIDE;
	rect.y = pos.GetY() * Game::TILE_SIDE;

	// 3. Frame de la animacion
	
		if (anim == 0) anim = 1;
		else anim = 0;
	

	// Se renderiza.
	texturaKoopa->renderFrame(rect, 0, anim);

	if (Game::DEBUG) {
		Point2D<float> nextPos = pos + dir * MOVE_SPEED;
		SDL_Rect rect2 = createRect(nextPos.GetX() * Game::TILE_SIDE, nextPos.GetY() * Game::TILE_SIDE);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		SDL_RenderDrawRect(renderer, &rect2);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}


void Koopa::update() {

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
			// Moverse en las X
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

Collision::collision Koopa::hit(const SDL_Rect& other, bool fromPlayer) {
	// collides, damages, intersectrect.
	Collision::collision colKoopa;
	SDL_Rect col = createRect(pos.GetX() * Game::TILE_SIDE, pos.GetY() * Game::TILE_SIDE);

	//Colisiona un rect que viene de fuera con el del koopa.

	if (fromPlayer) {
		colKoopa.collides = SDL_IntersectRect(&col, &other, &colKoopa.intersectRect);
		if (colKoopa.collides) {
			if (other.y < col.y)
				dead = true;
			else if (colKoopa.intersectRect.h > col.h) colKoopa.damages = true;
			else colKoopa.fromEnemy = true;
		}
	}
	return colKoopa;
}