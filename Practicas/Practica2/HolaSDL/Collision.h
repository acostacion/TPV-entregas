#pragma once
struct Collision
{
	// ¿A quién afecta esta colisión?
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		BOTH = 3,	// afecta a ambos
	};

	// Tipo de resultado de la colisión
	enum Result {
		NONE,		// no ha habido colisión
		DAMAGE,		// la colisión produce daño
		OBSTACLE,	// la colisión impide el movimiento
	};

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colisión horizontal
	int vertical = 0;     // profundidad de la colisión vertical
};
const Collision NO_COLLISION = { Collision::NONE, 0, 0 };


