#include "TileMap.h"

TileMap::TileMap(){
	// Constructora default -> todo a nullptr.
	texture = nullptr;
	game = nullptr;
}

TileMap::TileMap(std::istream& entrada, Game* _game) {
	
	// Asigna game y carga la textura BACKGROUND valiéndose del game.
	game = _game;
	texture = game->getTexture(Game::BACKGROUND);

	// Lee el archivo CSV.
	while (!std::cin) {
		int c = 0;
		char cAux = ','; // Se separa el archivo por comas.
		std::vector<int> fila;

		// Mientras cAux siga obteniendo ","... (lee la fila).
		while (cAux == ',') {
			// Lee el entero y lo añade a la fila actual.
			entrada >> c; 
			fila.push_back(c);

			// Get() lee el siguiente char (",").
			cAux = entrada.get();
		}
		if (!fila.empty()) {
			// Cuando se llena una fila, la mete al tilemap.
			map.push_back(fila); 
		}
	}
	/*APUNTES:
	* entrada.get(): extrae caracteres de un istream.
	* fila.push_back():
	* ...*/
	
}

void TileMap::Render() {
	// Filas y columnas totales.
	//SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	//int fils = sizeof map / sizeof map[0]; // filas
	//int cols = (sizeof map[0] / sizeof(map[0][0]))%9; // columnas


	int valor = TILE_MAP;
	int x0 = game->getMapOffset() / valor;
	int d0 = game->getMapOffset() % valor;
	SDL_Rect destRect;
	destRect.w = TILE_SIDE;
	destRect.h = TILE_SIDE;

	for (int i = 0; i < Game::WIN_WIDTH; i++) {
		for (int j = 0; j < Game::WIN_HEIGHT; j++ ) {
			int indice = map[x0 + i][j];
			int fx = indice % 9, fy = indice / 9;
			destRect.x = i * TILE_SIDE -d0;
			destRect.y = j * TILE_SIDE;
			texture->renderFrame(destRect, fx, fy);
		}
	}
}


void TileMap::Update() {
	Render();
}
