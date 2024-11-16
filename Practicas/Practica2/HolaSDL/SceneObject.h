#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Collision.h"


class SceneObject : public GameObject{ // SceneObject hereda de GameObject.
protected:
	// Atributos.
	Point2D<float>pos;
	float width, height;

	// Métodos.
	SceneObject(Game*, Point2D<float>&, float, float);

	virtual Collision::collision hit(const SDL_Rect& other, bool fromPlayer) = 0;
	virtual ~SceneObject();
};

