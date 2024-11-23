#pragma once
#include "SceneObject.h"

class Game;

class Enemy : public SceneObject
{
protected:
	// Referencias.
	Game* game = nullptr;
	Texture* texture = nullptr;

	SDL_Rect collider;

	Point2D<float> pos;
	Point2D<float> dir = Point2D<float>(-1, 0);

	bool isGrounded = true;
	bool frozen = true;
	bool dead = false;

	const int MARGIN_Y = 5;
	const int MARGIN_X = 5;
	const float GRAVITY = 0.1f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.
	const float MAX_FALL_SPEED = 0.2f;

	int timer = 3;
	int anim = 0;

	SDL_Rect createRect(float, float);

public:
	Enemy(Game* _game, std::istream&);

	virtual void render(SDL_Renderer* renderer) override;
	virtual void update() override;
	virtual Collision::collision hit(const SDL_Rect&, bool) override;
};

