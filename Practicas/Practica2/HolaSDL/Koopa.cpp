#include "CheckML.h"
#include "Koopa.h"

Koopa::Koopa(Game * _game, std::istream& entrada, int _points) : Enemy(_game, entrada, _points){

}

void Koopa::render(SDL_Renderer* renderer) const {
    SDL_Rect rect = createRect(pos.GetX() - game->getMapOffset(), pos.GetY());
    

    // Se renderiza.
    textura->renderFrame(rect, 0, anim);

    if (Game::DEBUG) {
        Point2D<float> nextPos = pos + dir * moveSpeed;
        SDL_Rect rect2 = createRect(
            nextPos.GetX() * Game::TILE_SIDE - game->getMapOffset(),
            nextPos.GetY() * Game::TILE_SIDE);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
        SDL_RenderDrawRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
    }
}


void Koopa::update() {
	if (!isShell) {
		Enemy::update(); // Movimiento base para Koopa normal
	}
	else {
		tryToMove({ 2, 0 }, true); // Movimiento de caparazón si es lanzado
	}
}


void Koopa::launchShell(const SDL_Rect& attackRect) {
	// Lógica para lanzar la caparazón como proyectil
	int direction = attackRect.x < pos.GetX() ? 1 : -1;
	dir.SetX(direction * 5); // Velocidad del caparazón
}

//Collision::collision Koopa::hit(const SDL_Rect& other, bool fromPlayer) {
//	// collides, damages, intersectrect.
//	Collision::collision colKoopa;
//	SDL_Rect col = createRect(pos.GetX() * Game::TILE_SIDE, pos.GetY() * Game::TILE_SIDE);
//
//	//Colisiona un rect que viene de fuera con el del koopa.
//
//	if (fromPlayer) {
//		colKoopa.collides = SDL_IntersectRect(&col, &other, &colKoopa.intersectRect);
//		if (colKoopa.collides) {
//			if (other.y < col.y)
//				dead = true;
//			else if (colKoopa.intersectRect.h > col.h) colKoopa.damages = true;
//			else colKoopa.fromEnemy = true;
//		}
//	}
//	return colKoopa;
//}

Collision Koopa::hit(const SDL_Rect& attackRect, Collision::Target) {
    if (!dead) {
        if (isShell) {
            // Si está en forma de caparazón, se lanza como proyectil
            launchShell(attackRect);
        }
        else {
            // Cambiar a forma de caparazón
            isShell = true;
            points = 0; // Sin puntos por cambiar de forma
            // Cambiar sprite o animación
        }
    }
    else {
        hit(attackRect, isFromPlayer); // Comportamiento base
    }
}