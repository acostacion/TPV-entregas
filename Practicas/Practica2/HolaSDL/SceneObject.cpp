#include "SceneObject.h"

SceneObject::SceneObject(Game* _game, Point2D<float>& _pos, Point2D<float>& _dir, Game::TextureName _textura) : GameObject(_game){
	pos = _pos;
	dir = _dir;
	textura = game->getTexture(_textura);
}
