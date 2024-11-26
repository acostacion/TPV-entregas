#include "checkML.h"
#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* game, std::istream& in) : Enemy(game, in){
    texture = game->getTexture(Game::GOOMBA);
}

void Goomba::render(SDL_Renderer * renderer) {
    Enemy::render(renderer);
}

void Goomba::update() {
    Enemy::update();
}