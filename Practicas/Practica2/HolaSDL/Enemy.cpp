#include "checkML.h"
#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* _game, std::istream& in) : SceneObject(_game, pos, width, height, texture){
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	dir = Point2D<float>(-1, 0);

	isGrounded = true;
	frozen = true;
	timer = 3;
	anim = 0;
}


SDL_Rect Enemy::createRect(float x, float y) {
	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posición.
	rect.w = texture->getFrameWidth() * 2;
	rect.h = texture->getFrameHeight() * 2;
	rect.x = x;
	rect.y = y;

	return rect;
}

virtual void render(SDL_Renderer* renderer) override;
virtual void update() override;
virtual Collision::collision hit(const SDL_Rect&, bool) override;

// Getters
float getX()const { return this->pos.GetX(); }
float getY()const { return this->pos.GetY(); }
bool getFrozen()const { return frozen; }
Point2D<float> getDir()const { return dir; }
bool isDead()const { return dead; }



