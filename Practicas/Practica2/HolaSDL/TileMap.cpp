#include "CheckML.h"
#include "TileMap.h"
#include "SDL_rect.h"


TileMap::TileMap(Game* _game, std::istream& entrada)
	:SceneObject(_game, entrada) {
	int x = 0, y = 0;
	textura = _game->getTexture(Game::BACKGROUND);
	try {
		// Lee el archivo CSV.
		while (entrada) {
			int c = 0;
			char cAux = ','; // Se separa el archivo por comas.
			std::vector<int> fila;

			x = 0;
			// Mientras cAux siga obteniendo ","... (lee la fila).
			while (cAux == ',') {
				// Lee el entero y lo añade a la fila actual.
				entrada >> c;
				fila.push_back(c);
				SDL_Rect rect;
				rect.w = Game::TILE_SIDE;
				rect.h = Game::TILE_SIDE;
				rect.x = x;
				rect.y = y;
				// Get() lee el siguiente char (",").
				x++;
				cAux = entrada.get();
			}
			map.push_back(fila);
			y++;
		}
	}
	catch (...) {
		std::cout << "Error creando TileMap.";
	}
}

void TileMap::render(SDL_Renderer* renderer) const{

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
			// indice en el conjunto de patrones de la matriz de ?ndices
			int indice = map[j][i + x0];
			if (indice != - 1) {
				// Separa n?mero de fila y de columna
				int fx = indice % 9;
				int fy = indice / 9;

				rect.x = -d0 + i * Game::TILE_SIDE;
				rect.y = j * Game::TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				textura->renderFrame(rect, fy, fx);

				if (Game::DEBUG) {
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
					SDL_RenderDrawRect(renderer, &rect);
					SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
				}
			}
		}
	}
}

void TileMap::update() {

}


Collision::collision TileMap::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision::collision colres;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / Game::TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / Game::TILE_SIDE;

	for (int row = rect.y / Game::TILE_SIDE; row <= row1 && !colres.collides; ++row)
		for (int col = rect.x / Game::TILE_SIDE; col <= col1 && !colres.collides; ++col) {
			int indice = map[row][col];
			if (indice != -1 && indice % textura->getNumColumns() < OBSTACLE_THRESHOLD) {
				SDL_Rect tile = { col * Game::TILE_SIDE,row * Game::TILE_SIDE, Game::TILE_SIDE, Game::TILE_SIDE };
				if (SDL_IntersectRect(&tile, &rect, &colres.intersectRect)) {
					colres.collides = true;
				}
			}
		}

	return colres;

}

