#include <vector>
#include "Texture.h"


#pragma once

class TileMap
{
private:
	std::vector<std::vector<int>> map;
	Texture* texture; // Conjunto de patrones.

	//int NUM_TEXTURES = 62;

public:
	TileMap(std::istream&);
	void Render();
	void Update();
	void Hit();

};

