#pragma once
class Collision {
public:
	struct collision {
		bool collides;
		bool damages;
		SDL_Rect intersectRect;

		operator bool() const { return collides; }
	    bool getDamages() const { return damages; }
		SDL_Rect getRectInter() const { return intersectRect; }
	};
};


