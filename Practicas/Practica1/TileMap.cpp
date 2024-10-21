
#include "TileMap.h"
#include <iostream>
#include <vector>


TileMap::TileMap(std::istream& entrada, Texture* textura) {
	char c;
	int i = 0, j = 0;
	std::vector<std::vector<int>> nuevotileMap;
	map = nuevotileMap;
	//texture = new Texture[NUM_TEXTURAS];
	texture = textura;
	destRect.w = cellW;
	destRect.h = cellH;
	// Va almacenando cada elemento.
	while (entrada) {
		while (entrada) {
			entrada >> map[i][j] >> c;
			j++;
		}
		if(entrada)j = 0;
		i++;
	}
	colAct = 0;
}

void TileMap::Render(SDL_Renderer* renderer) {
	// Filas y columnas totales.
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	int fils = sizeof map / sizeof map[0]; // filas
	int cols = (sizeof map[0] / sizeof(map[0][0]))%9; // columnas

	for (int i = 0; i < fils; i++) {
		for (int j = 0 + colAct; j < cols; j++ ) {
			destRect.x = i * cellW;
			destRect.y = j * cellH;
			if (map[i][j] != -1) {
				texture->renderFrame(destRect, i, j);
			}


		}
	}

	SDL_RenderPresent(renderer);
}