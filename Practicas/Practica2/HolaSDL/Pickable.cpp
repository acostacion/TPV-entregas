#include "Pickable.h"

Pickable::Pickable(Game* _game, std::istream& entrada) : SceneObject(_game, entrada) {

}

Pickable::Pickable(Game* _game, const Point2D<float>& pos) : SceneObject(_game, pos, {-1,0}) {

}


Collision
Pickable::hit(const SDL_Rect& region, Collision::Target target)
{
	// Comprueba si hay colisión
	SDL_Rect ownRect = getCollisionRect();

	if (target == Collision::ENEMIES && SDL_HasIntersection(&ownRect, &region)) {
		triggerAction();  // método protegido que implementará la subclase
		delete this;
	}

	return NO_COLLISION; // constante Collision{}
}