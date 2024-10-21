#include <vector>
#include "Texture.h"
#include "Game.h"


#pragma once

class TileMap
{
private:
	std::vector<std::vector<int>> map;
	Texture* texture; // Conjunto de patrones.
	int colAct;
	SDL_Rect destRect;
	uint cellW = Game::WIN_WIDTH / 18, cellH  = Game::WIN_HEIGHT / 16;
	//int NUM_TEXTURES = 62;

public:
	TileMap(std::istream&, Texture*);
	void Render();
	void Update();
	void Hit();

};

