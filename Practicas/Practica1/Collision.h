#pragma once
class Collision {
public:
	bool collides;
	bool damages;
	
	operator bool() const { return collides; }
};


