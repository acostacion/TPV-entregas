#include "Enemy.h"

Enemy::Enemy(Game* _game, std::istream entrada, int _points) : SceneObject(_game, entrada), points(_points), dead(false) {

}

