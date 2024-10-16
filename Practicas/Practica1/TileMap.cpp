#include "Texture.h"
#include "TileMap.h"
#include <iostream>
#include <vector>


TileMap::TileMap(std::istream& entrada) {
	char c;
	int i = 0, j = 0;
	std::vector<std::vector<int>> nuevotileMap;
	map = nuevotileMap;
	//texture = new Texture[NUM_TEXTURAS];

	// Va almacenando cada elemento.
	while (entrada) {
		while (entrada) {
			entrada >> map[i][j] >> c;
			j++;
		}
		if(entrada)j = 0;
		i++;
	}
}

void TileMap::Render() {
	int fils = sizeof map / sizeof map[0]; // filas
	int cols = sizeof map[0] / sizeof(map[0][0]); // columnas

	for (int i = 0; i < fils; i++) {
		for (int j = 0; j < cols; j++ ) {
			
		}
	}
}