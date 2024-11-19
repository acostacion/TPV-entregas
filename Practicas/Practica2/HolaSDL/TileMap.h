#pragma once

#include "Texture.h"
#include "SceneObject.h"
#include "Game.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include "Collision.h"

using uint = unsigned int;

class Game;

class TileMap : SceneObject
{
private:
	std::vector<std::vector<int>> map; // Tilemap.
	
public:
	static constexpr uint TILE_MAP = 32;
	const int OBSTACLE_THRESHOLD = 4; // constante

	TileMap(std::istream& entrada, Game* _game); // Constructora desde flujo de entrada y referencia al juego.
	void render(SDL_Renderer* renderer);
	void update();
	Collision::collision hit(const SDL_Rect& rect, bool fromPlayer);
};

