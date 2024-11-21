#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* _game, Point2D<float>& _pos, float _w, float _h) : GameObject(_game) {
	pos = _pos;
	width = texture->getFrameWidth(); // Inicializa el ancho con el tamaño de un frame de la textura
	height = texture->getFrameHeight(); // Inicializa la altura con el tamaño de un frame de la textura
}