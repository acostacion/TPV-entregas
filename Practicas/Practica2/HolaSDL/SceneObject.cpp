#include "checkML.h"
#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* _game, Point2D<float>& _pos, float& _w, float& _h, Texture* _texture) : GameObject(_game) {
	pos = _pos;
	texture = _texture;
	width = texture->getFrameWidth(); // ancho con size del frame de la textura
	height = texture->getFrameHeight(); // altura con size del frame de la textura
}