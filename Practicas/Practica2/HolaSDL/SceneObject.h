#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Collision.h"


class SceneObject : public GameObject{ // SceneObject hereda de GameObject.
protected:
	// Atributos.
	Point2D<float> pos;
	Point2D<float> dir;
	Texture* textura;
	int anim;
	int timer;

	const int MARGIN_Y = 5;
	const int MARGIN_X = 5;

	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.


	// Métodos.
	SceneObject(Game*, Point2D<float>&, Point2D<float>&, Game::TextureName);
	virtual void render(SDL_Renderer* renderer);


	virtual Collision::collision hit(const SDL_Rect& other, bool fromPlayer) = 0;
	virtual ~SceneObject();

	SDL_Rect createRect(float, float);

	float getX()const { return this->pos.GetX(); }

	Point2D<float> getPos();
	Point2D<float> getDir();
};

inline Point2D<float>
SceneObject::getPos() {
	return pos;
}

inline Point2D<float>
SceneObject::getDir() {
	return dir;
}