#include "Enemy.h"

Enemy::Enemy(Game* _game, std::istream& entrada, int _points) : SceneObject(_game, entrada), points(_points) {
	frozen = true;
}

void Enemy::givePointsToPlayer() {
	// Lógica para sumar puntos al jugador
	if (game) {
		game->addPoints(points);
	}
}

void
Enemy::update()
{
	// Acelra la velocidad con la gravedad
	if (speed.GetY() < SPEED_LIMIT)
		speed = speed +  Point2D<float>({0, Game::GRAVITY});

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Point2D<float> realSpeed = speed;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.SetX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		speed.SetX(-speed.GetX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		speed.SetY(0);

	SceneObject::update();
}
