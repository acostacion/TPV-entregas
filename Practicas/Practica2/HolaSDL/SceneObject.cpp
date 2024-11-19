#include "SceneObject.h"

SceneObject::SceneObject(Game* _game, Point2D<float>& _pos, Point2D<float>& _dir) : GameObject(_game){
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


SDL_Rect SceneObject::createRect(int x , int y) {
	return{ x, y, textura->getFrameWidth() * 2,textura->getFrameHeight() * 2 };
}

void SceneObject::update() {
	// Actualiza la posición basada en la dir
	Point2D<float> nextPos = pos + dir;
}



void SceneObject::tryToMove(Vector2D<int> velocity, bool allowVertical) {
	nextPosition = { pos.GetX() + velocity.GetX(),pos.GetY() + velocity.GetY()};
}
