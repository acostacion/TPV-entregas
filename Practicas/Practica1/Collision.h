#pragma once
class Collision {
public:
	struct collision {
		bool collides; // con tilemap
		bool damages; // player con enemigo collides
		SDL_Rect intersectRect;

		operator bool() const { return collides; }
	};
};


