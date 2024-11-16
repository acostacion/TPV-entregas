#include "SceneObject.h"

SceneObject::SceneObject(Game* _game, Point2D<float>& _pos, float _w, float _h) : GameObject(_game){
	pos = _pos;
	width = _w;
	height = _h;
}
