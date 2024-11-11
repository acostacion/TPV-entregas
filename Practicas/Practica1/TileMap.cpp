#include "TileMap.h"
#include "SDL_rect.h"
#
TileMap::TileMap(){
	// Constructora default -> todo a nullptr.
	texture = nullptr;
	game = nullptr;
}

TileMap::TileMap(std::istream& entrada, Game* _game)  {
	
	// Asigna game y carga la textura BACKGROUND valiéndose del game.
	game = _game;
	renderer = game->getRender();
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

	int i = rect.y / Game::TILE_SIDE;
	int row = (rect.y + rect.h) / Game::TILE_SIDE;
	int col = (rect.x + rect.w) / Game::TILE_SIDE;
	bool colisionado = false;
	bool esObs = false;
	while (i < map.size() && i <= row && (!colisionado || colisionado && !esObs)) {
		int j = rect.x / Game::TILE_SIDE;
		while (j < map[i].size() && j <= col && (!colisionado || colisionado && !esObs)) {
			if (map[i][j] != -1) {
				SDL_Rect aux = { j * Game::TILE_SIDE,i * Game::TILE_SIDE, Game::TILE_SIDE, Game::TILE_SIDE };
				if (SDL_IntersectRect(&aux, &rect, &colres.intersectRect)) {
					colisionado = true;
					if (map[i][j] % texture->getNumColumns() < OBSTACLE_THRESHOLD) {
						esObs = true;
					}
				}
			}
			++j;
		}
		++i;
	}
	colres.collides = colisionado && esObs;

	return colres;

}

