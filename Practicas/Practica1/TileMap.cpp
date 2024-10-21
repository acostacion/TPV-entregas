
#include "TileMap.h"
#include <iostream>
#include <vector>


TileMap::TileMap(std::istream& entrada, Game* _game) {
	char c;
	int i = 0, j = 0;
	//texture = new Texture[NUM_TEXTURAS];
	game = _game;
	texture = _game->getTexture(Game::BACKGROUND);
	std::vector<int> fila;
	int e = 0;
	// Va almacenando cada elemento.
	while (entrada) {
		while (entrada) {
			entrada >> e >> c;
			fila.push_back(e);
			j++;
		}
		if(entrada)j = 0;
		i++;
		map.push_back(fila);
	}
}

void TileMap::Render(SDL_Renderer* renderer) {
	// Filas y columnas totales.
	//SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	//int fils = sizeof map / sizeof map[0]; // filas
	//int cols = (sizeof map[0] / sizeof(map[0][0]))%9; // columnas

	int valor = this->TILE_MAP;
	int x0 = game->getMapOffset() / valor;
	int d0 = game->getMapOffset() % valor;

	for (int i = 0; i < Game::WIN_WIDTH; i++) {
		for (int j = 0; j < Game::WIN_HEIGHT; j++ ) {
			int indice = map[x0 + i][j];
			int fx = indice % 9, fy = indice / 9;
			this->destRect.x = i * TILE_SIDE -d0;
			this->destRect.y = j * TILE_SIDE;
			this->texture->renderFrame(destRect, fx, fy);
		}
	}
}