﻿#include "Mushroom.h"


Mushroom::Mushroom(Game* _game, float x, float y) {
	game = _game;
	pos = Point2D<float>(x, y);
	dir = Point2D<float>(1, 0);
	isGrounded = false;
	dead = false;
	texturaMushroom = game->getTexture(Game::MUSHROOM);
}

SDL_Rect Mushroom::getRect(bool forRender) const {
	SDL_Rect rect;

	rect.x = pos.GetX() * Game::TILE_SIDE;
	rect.y = pos.GetY() * Game::TILE_SIDE;
	if (forRender) {
		rect.x = (pos.GetX() * Game::TILE_SIDE) - game->getMapOffset();
	}
	
	rect.w = texturaMushroom->getFrameWidth();
	rect.h = texturaMushroom->getFrameHeight();

	return rect;
}

SDL_Rect Mushroom::createRect(float x, float y) {
	// Se crea el rect.
	SDL_Rect rect;

	// Se le da dimensiones y posición.
	
	rect.w = texturaMushroom->getFrameWidth();
	rect.h = texturaMushroom->getFrameHeight();
	
	rect.x = x;
	rect.y = y;

	return rect;
}

void Mushroom::render(SDL_Renderer* renderer) {
	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posici�n.
  	rect.w = texturaMushroom->getFrameWidth() * 2;
	rect.h = texturaMushroom->getFrameHeight() * 2;
	rect.x = pos.GetX() * Game::TILE_SIDE;
	rect.y = pos.GetY() * Game::TILE_SIDE;
	texturaMushroom->renderFrame(rect, 0, 1);

	if (Game::DEBUG) {
		Point2D<float> nextPos = pos + dir * MOVE_SPEED;
		SDL_Rect rect2 = createRect(
			nextPos.GetX() * Game::TILE_SIDE,
			nextPos.GetY() * Game::TILE_SIDE);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		SDL_RenderDrawRect(renderer, &rect2);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Mushroom::update() {
	pos = pos + dir * MOVE_SPEED;
}

Collision::collision Mushroom::hit(const SDL_Rect& other, bool fromPlayer) {
	Collision::collision res;
	SDL_Rect rect = getRect(false);
	if(SDL_IntersectRect(&other, &rect, &res.intersectRect)) {
		res.fromMushroom = true;
		res.collides = true;
		if (fromPlayer) { // se elimina y cambia el player
			dead = true;
		}
		else {// se invierte
			dir.SetX(-dir.GetX());
		}
	}
	

	return res;
}