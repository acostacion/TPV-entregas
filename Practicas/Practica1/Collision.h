#pragma once
class Collision {
public:
	bool collides;
	bool damages;
	SDL_Rect intersectRect;
	
	operator bool() const { return collides; }


};


