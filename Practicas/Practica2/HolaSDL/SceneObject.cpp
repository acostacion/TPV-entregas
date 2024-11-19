#include "CheckML.h"
#include "Game.h"

#include "SceneObject.h"

SceneObject::SceneObject(Game* _game, const Point2D<float>& _pos, const Point2D<float>& _dir) : GameObject(_game){
	pos = _pos - Point2D<float>(0, 1);
	dir = _dir;
	anim = 0;
	timer = 0;
	isGrounded = false;
	dead = false;
	moveSpeed = 0.3f;
}

SceneObject::SceneObject(Game* _game, std::istream& entrada) : GameObject(_game) {
	entrada >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // ajusta pos.
	dir = Point2D<float>(-1, 0);
	dead = false;
	isGrounded = false;
	anim = 0;
	timer = 0;
}


SDL_Rect SceneObject::createRect(int x , int y) const {
	return{ x, y, textura->getFrameWidth() * 2,textura->getFrameHeight() * 2 };
}

SDL_Rect
SceneObject::getCollisionRect() const
{
	return SDL_Rect{
		(int)pos.GetX(),
		(int)pos.GetY() - height,  // la referencia es la esquina inferior izquierda
		width,
		height
	};
}

SDL_Rect
SceneObject::getRenderRect() const
{
	return SDL_Rect{
		(int)pos.GetX() - game->getMapOffset(),  // coordenadas de la ventana
		(int)pos.GetY() - height,
		width,
		height
	};
}



Collision SceneObject::tryToMove(const Vector2D<float>& speed, Collision::Target target) {
	Collision collision;
	SDL_Rect rect = getCollisionRect();

	// Intenta moverse en vertical
	if (speed.GetY() != 0) {
		rect.y += speed.GetY();

		collision = game->checkCollision(rect, target);

		// Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
		int fix = collision.vertical * (speed.GetY() > 0 ? 1 : -1);
		pos = pos + Point2D<float>(0, speed.GetY() - fix);

		rect.y -= fix; // recoloca la caja para la siguiente colisión
	}

	collision.horizontal = 0; // la horizontal del choque vertical da igual

	// Intenta moverse en horizontal
	if (speed.GetX() != 0) {
		rect.x += speed.GetX();

		Collision partial = game->checkCollision(rect, target);

		// Copia la información de esta colisión a la que se devolverá
		collision.horizontal = partial.horizontal;

		if (partial.result == Collision::DAMAGE)
			collision.result = Collision::DAMAGE;

		pos = pos + Point2D<float>{speed.GetX() - collision.horizontal * (speed.GetX() > 0 ? 1 : -1), 0};
	}

	return collision;
}
