#include "TileMap.h"
#include "SDL_rect.h"
#
TileMap::TileMap(){
	// Constructora default -> todo a nullptr.
	texture = nullptr;
	game = nullptr;
}

TileMap::TileMap(std::istream& entrada, Game* _game) {
	
	// Asigna game y carga la textura BACKGROUND valiéndose del game.
	game = _game;
	texture = game->getTexture(Game::BACKGROUND);
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

SDL_Rect TileMap::createRect(int w, int h, int x, int y) {
	// Se crea el rect.
	SDL_Rect rect;

	// Se le da dimensiones y posición.
	rect.w = w;
	rect.h = h;
	rect.x = x;
	rect.y = y;

	return rect;
}

Collision::collision TileMap::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision::collision colres;
	colres.collides = false;
	colres.damages = false;
	colres.intersectRect = createRect(0,0,0,0);

	constexpr int OBSTACLE_THRESHOLD = 4; // constante

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / Game::TILE_SIDE;
	int col0 = rect.x / Game::TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h) / Game::TILE_SIDE;
	int col1 = (rect.x + rect.w) / Game::TILE_SIDE;

	for (int row = row0; row <= row1; ++row)
		for (int col = col0; col <= col1; ++col)
			if (map[row][col] % texture->getNumColumns() < OBSTACLE_THRESHOLD)
			{
				SDL_Rect rectTile, res;
				rectTile.w = Game::TILE_SIDE;
				rectTile.h = Game::TILE_SIDE;
				rectTile.x = row * Game::TILE_SIDE;
				rectTile.y = col * Game::TILE_SIDE;

				res = createRect(0,0,0,0);
				colres.collides = SDL_IntersectRect(&rectTile, &rect, &res );
				colres.intersectRect = res;

				return colres;
			}


	return colres;
}

