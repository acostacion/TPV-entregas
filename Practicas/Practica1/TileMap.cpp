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
	while (entrada) {
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
		map.push_back(fila);
	}
}

void TileMap::render() {

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = game->getMapOffset() / TILE_MAP;
	// Anchura oculta de esa primera columna
	int d0 = game->getMapOffset() % TILE_MAP;

	// tamaño del cuadro a pintarse
	SDL_Rect rect;
	rect.w = Game::TILE_SIDE;
	rect.h = Game::TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < Game::WIN_TILE_WIDTH + 1; ++i) {
		for (int j = 0; j < Game::WIN_TILE_HEIGHT; ++j) {
			// ?ndice en el conjunto de patrones de la matriz de ?ndices
			int indice = map[j][i + x0];
			if (indice != - 1) {
				// Separa n?mero de fila y de columna
				int fx = indice % 9;
				int fy = indice / 9;

				rect.x = -d0 + i * Game::TILE_SIDE;
				rect.y = j * Game::TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				texture->renderFrame(rect, fy, fx);
			}
		}
	}
}


void TileMap::update() {
	
}
