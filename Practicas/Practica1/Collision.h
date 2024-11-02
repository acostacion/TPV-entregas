#pragma once
#include <fstream>
#include <iostream>
class Collision {
public:
	bool collides;
	bool damages;
	
	operator bool() const { return collides; }
};

