#pragma once

#include "SceneObject.h"
#include <vector>
using uint = unsigned int;

class Game;

class TileMap : SceneObject
{
private:
	std::vector<std::vector<int>> map; // Tilemap.
	
public:
	static constexpr uint TILE_MAP = 32;
	const int OBSTACLE_THRESHOLD = 4; // constante

	TileMap(Game* , std::istream&); // Constructora desde flujo de entrada y referencia al juego.
	void render(SDL_Renderer* renderer)const override;
	void update() override;
	void animation() override;

	Collision hit(const SDL_Rect&, Collision::Target) override;

};

