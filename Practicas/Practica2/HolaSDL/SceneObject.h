#pragma once
#include "GameObject.h"
#include "gameList.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Collision.h"

class SceneObject : public GameObject{ // SceneObject hereda de GameObject.
protected:
	// Atributos.
	Point2D<float>pos;
	float width, height;

	// Métodos.
	//SceneObject(Game* _game, Point2D<float>& _pos, float _w, float _h)

	virtual Collision::collision hit(const SDL_Rect& other, bool fromPlayer) = 0;
	//virtual ~SceneObject();
};

