#include "checkML.h"
#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* _game, Point2D<float>& _pos, float& _w, float& _h, Texture* _texture) : GameObject(_game) {
	pos = _pos;
	texture = _texture;
	width = _w;
	height = _h;
}

Collision SceneObject::tryToMove(const Vector2D<float>& speed, Collision::Target target)
{
	// El método protegido tryToMove concentra el código de la comprobación
	// de las colisiones para todos los objetos del juego. Recibe un vector
	// con el movimiento que se quiere aplicar al objeto, prueba el movimiento
	// en cambos ejes y devuelve la información de tipo Collision.
	Collision collision;
	SDL_Rect rect = getCollisionRect();

	// Intenta moverse en vertical
	if (speed.GetY() != 0) {
		rect.y += speed.GetY();

		collision = game->checkCollision(rect, target);

		// Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
		int fix = collision.vertical * (speed.GetY() > 0 ? 1 : -1);
		pos.SetX(pos.GetX());
		pos.SetY(pos.GetY() + speed.GetY() - fix);

		// Obs: a ? b : c es el operador ternario: vale b si a es cierto y c en caso contrario

		rect.y -= fix; // recoloca la caja para la siguiente colisión
	}

	collision.horizontal = 0; // la horizontal del choque vertical da igual

	// Intenta moverse en horizontal
	// (podría ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
	if (speed.GetX() != 0) {
		rect.x += speed.GetX();

		Collision partial = game->checkCollision(rect, target);

		// Copia la información de esta colisión a la que se devolverá
		collision.horizontal = partial.horizontal;

		if (partial.result == Collision::DAMAGE)
			collision.result = Collision::DAMAGE;

		pos.SetX(pos.GetX() + speed.GetX() - collision.horizontal * (speed.GetX() > 0 ? 1 : -1));
		pos.SetY(pos.GetY());
	}

	return collision;
}

SDL_Rect SceneObject::getCollisionRect() {
	return SDL_Rect{
		(int)pos.GetX(),
		(int)pos.GetY() - (int)height,  // la referencia es la esquina inferior izquierda
		(int)width,
		(int)height
	};
}

SDL_Rect SceneObject::getRenderRect() const
{
	return SDL_Rect{
		(int)pos.GetX() - game->getMapOffset(),  // coordenadas de la ventana
		(int)pos.GetY() - (int)height,
		(int)width,
		(int)height
	};
}

