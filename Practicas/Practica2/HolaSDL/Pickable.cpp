#include "Pickable.h"

Collision Pickable::hit(const SDL_Rect& region, Collision::Target target)
{
	// Comprueba si hay colisi�n
	SDL_Rect ownRect = getCollisionRect();

	if (target == Collision::ENEMIES && SDL_HasIntersection(&ownRect, &region)) {
		triggerAction();  // m�todo protegido que implementar� la subclase
		delete this;
	}

	return NO_COLLISION; // constante Collision{}
}
