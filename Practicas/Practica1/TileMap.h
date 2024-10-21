#include <vector>
#include "Texture.h"
#include "Game.h"


#pragma once

class TileMap
{
private:
	std::vector<std::vector<int>> map;
	Game* game;
	Texture* texture; // Conjunto de patrones.
	SDL_Rect destRect;
	//uint cellW = Game::WIN_WIDTH / 18, cellH  = Game::WIN_HEIGHT / 16;

public:
	static constexpr uint TILE_SIDE = 16;
	static constexpr uint TILE_MAP = 32;

	TileMap(std::istream& entrada, Game* _game);
	void Render(SDL_Renderer*);
	//void Update();
	//void Hit();

};

