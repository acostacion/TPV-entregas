#pragma once

#include "Texture.h"
#include "Game.h"
#include <SDL.h>

#include <fstream>
#include <iostream>

using uint = unsigned int;

class Game;

class TileMap
{
private:
	std::vector<std::vector<int>> map;
	Texture* texture; // Conjunto de patrones.
	Game* game;

public:

	static constexpr uint TILE_SIDE = 16;
	static constexpr uint TILE_MAP = 32;
	TileMap();
	TileMap(std::istream&, Game*);
	void Render();
	void Update();
	//void Hit();



};

