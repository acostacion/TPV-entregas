#include "CheckML.h"
#include "TileMap.h"
#include "Game.h"
#include "SceneObject.h"

TileMap::TileMap(std::istream& entrada, Game* _game) 
	: SceneObject(_game, Vector2D<float>(0,0), TILE_MAP, TILE_MAP, nullptr) {
	texture = _game->getTexture(Game::BACKGROUND);

	try {
		int x = 0, y = 0;
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

void TileMap::render(SDL_Renderer* renderer) {

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = game->getMapOffset() / TILE_MAP;
	// Anchura oculta de esa primera columna
	int d0 = game->getMapOffset() % TILE_MAP;

	// tamaño del cuadro a pintarse
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WIN_TILE_WIDTH + 1; ++i) {
		for (int j = 0; j < WIN_TILE_HEIGHT; ++j) {
			// indice en el conjunto de patrones de la matriz de ?ndices
			int indice = map[j][i + x0];
			if (indice != - 1) {
				// Separa n?mero de fila y de columna
				int fx = indice % 9;
				int fy = indice / 9;

				rect.x = -d0 + i * TILE_SIDE;
				rect.y = j * TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				texture->renderFrame(rect, fy, fx);

				if (DEBUG) {
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

// REVISAR.
Collision TileMap::hit(const SDL_Rect& rect, Collision::Target target)
{
	Collision collisionResult;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / TILE_SIDE;

	for (int row = rect.y / TILE_SIDE; row <= row1 && collisionResult.result == Collision::NONE; ++row) {
		for (int col = rect.x / TILE_SIDE; col <= col1 && collisionResult.result == Collision::NONE; ++col) {
			int indice = map[row][col];
			if (indice != -1 && indice % texture->getNumColumns() < OBSTACLE_THRESHOLD) {
				SDL_Rect tile = { col * TILE_SIDE,row * TILE_SIDE, TILE_SIDE, TILE_SIDE };
				if (SDL_IntersectRect(&tile, &rect, nullptr)) {
					collisionResult.result = Collision::OBSTACLE;
					collisionResult.horizontal = col * TILE_SIDE;
					collisionResult.vertical = row * TILE_SIDE;
				}
			}
		}
	}

	return collisionResult;
}

