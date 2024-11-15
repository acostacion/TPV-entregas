#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Collision.h"


class SceneObject : public GameObject
{
private:
	Point2D<float>pos;
	float width, height;
public:
	SceneObject(Game* gameInstance, Point2D<float>& position, float w, float h) : GameObject(gameInstance) {
		pos = position;
		width = w;
		height = h;
	}

	virtual Collision::collision hit(const SDL_Rect& other, bool fromPlayer);
	void render()const override;
	void update() override;
	virtual ~SceneObject();
};

