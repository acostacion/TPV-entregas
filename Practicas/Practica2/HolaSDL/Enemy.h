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
	Point2D<float> dir;
	bool isGrounded;
	bool frozen;
	bool dead;
	const int MARGIN_Y = 5;
	const int MARGIN_X = 5;

	int timer;
	int anim;
	SDL_Rect createRect(float, float);

	const float GRAVITY = 0.1f;
	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.
	const float MAX_FALL_SPEED = 0.2f;

public:
	Enemy(Game* _game, std::istream&);
	virtual void render(SDL_Renderer* renderer) override;
	virtual void update() override;
	virtual Collision::collision hit(const SDL_Rect&, bool) override;

	// Getters
	float getX()const { return this->pos.GetX(); }
	float getY()const { return this->pos.GetY(); }
	bool getFrozen()const { return frozen; }
	Point2D<float> getDir()const { return dir; }
	bool isDead()const { return dead; }
};

