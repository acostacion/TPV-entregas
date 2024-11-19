#pragma once
class Collision {
public:

	bool collides = false; // con tilemap
	bool damages = false; // player con enemigo collides
	bool fromEnemy = false;
	bool fromMushroom = false;
	bool fromPlayer = false;
	bool fromSuperMario = false;
	SDL_Rect intersectRect;

	operator bool() const { return collides; }
	
};


