#pragma once
#include "Texture.h"
#include "Collision.h"
#include "SceneObject.h"
#include <vector>
#include <iostream>

using uint = unsigned int;
class Game;

class TileMap : public SceneObject
{
private:
	std::vector<std::vector<int>> map; // Tilemap.
	Texture* texture = nullptr; // Conjunto de patrones (textura con tiles).
	
public:
	static constexpr uint TILE_MAP = 32;
	const int OBSTACLE_THRESHOLD = 4; // constante

	TileMap(std::istream& entrada, Game* _game); // Constructora desde flujo de entrada y referencia al juego.
	
	void update()override;
	void render(SDL_Renderer* renderer) override;
	Collision hit(const SDL_Rect& rect, Collision::Target target) override;
};

