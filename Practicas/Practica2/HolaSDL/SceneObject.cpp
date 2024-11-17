#include "SceneObject.h"

SceneObject::SceneObject(Game* _game, Point2D<float>& _pos, Point2D<float>& _dir, Game::TextureName _textura) : GameObject(_game){
	pos = _pos;
	dir = _dir;
	textura = game->getTexture(_textura);
	width = textura->getFrameWidth();
	height = textura->getFrameHeight();
	anim = 0;
	timer = 0;
	dead = false;
	isGrounded = false;
}

SDL_Rect SceneObject::createRect(int x , int y) {
	return{ x, y, textura->getFrameWidth() * 2,textura->getFrameHeight() * 2 };
}


void SceneObject::tryToMove(Vector2D<int> velocity, bool allowVertical) {
	nextPosition = { pos.GetX() + velocity.GetX(),pos.GetY() + velocity.GetY()};
}
