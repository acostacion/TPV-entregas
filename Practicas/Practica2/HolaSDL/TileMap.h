#pragma once

#include "Texture.h"
#include "Game.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include "Collision.h"

using uint = unsigned int;

class Game;

class TileMap
{
private:
	std::vector<std::vector<int>> map; // Tilemap.
	Texture* texture; // Conjunto de patrones (textura con tiles).
	Game* game; // Puntero a instancia de game para acceder a sus cosas.
	
public:
	static constexpr uint TILE_MAP = 32;
	const int OBSTACLE_THRESHOLD = 4; // constante

	TileMap(std::istream&, Game*); // Constructora desde flujo de entrada y referencia al juego.
	void render(SDL_Renderer*);
	void update();
	Collision::collision hit(const SDL_Rect&, bool);
};

