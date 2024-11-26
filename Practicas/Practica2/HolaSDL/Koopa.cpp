#include "checkML.h"
#include "Koopa.h"
#include "Game.h"

Koopa::Koopa(Game* game, std::istream& in) : Enemy(game, in){
	texture = game->getTexture(Game::KOOPA);
}

void Koopa::render(SDL_Renderer* renderer) {
	Enemy::render(renderer);
}

void Koopa::update() {
	Enemy::update();
}