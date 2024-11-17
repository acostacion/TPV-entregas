#include "GameObject.h"

GameObject::GameObject(Game* _game) {
	game = _game;
}

GameObject::~GameObject() {}

void GameObject::render(SDL_Renderer* renderer) const {}