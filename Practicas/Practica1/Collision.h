#pragma once
class Collision {
public:
	struct collision {

		bool collides = false; // con tilemap
		bool damages = false; // player con enemigo collides
		bool fromEnemy = false;
		bool fromMushroom = false;

		SDL_Rect intersectRect;

		operator bool() const { return collides; }
	};
};


