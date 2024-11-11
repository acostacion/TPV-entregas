#include <string>
#include <sstream>
#include "Game.h"


using namespace std;

#pragma region texturas
// Esto define la textura.
struct TextureSpec
{
	const char* name;	// Ruta.
	uint numColumns;	// Nº de frames por cols.
	uint numRows;		// Nº de frames por fils.
};

// Directorio raíz texturas.
const string textureRoot = "../assets/";

// Texturas del juego.
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	// {Mapa, cols, fils}
	TextureSpec{"imgs/background.png", 9, 7}, 
	TextureSpec{"imgs/mario.png", 12, 1}, 
	TextureSpec{"imgs/supermario.png", 22, 1},
	TextureSpec{"imgs/goomba.png", 3, 1},
	TextureSpec{"imgs/blocks.png", 6, 1},
	TextureSpec{"imgs/koopa.png", 4, 1},
	TextureSpec{"imgs/mushroom.png", 1, 1},
};
#pragma endregion

// CONSTRUCTORA.
Game::Game() : seguir(true), mapOffset(0), reset(false) {
	// --- SDL ---.
	createSDL();

	// --- TEXTURAS ---.
	createTextures();

	Smario = false;

	// --- MAPAS ---.
	createTilemap();
	createEntitymap();

	//perro = new Dog(this, -textures[BACKGROUND]->getFrameWidth(), 390);
}

#pragma region Submétodos Constructora
void Game::createTextures() {
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		// Crea las texturas...
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(), // Dirección.
			textureSpec[i].numRows, // Filas.
			textureSpec[i].numColumns); // Columnas
	}
}

void Game::createSDL() {
	// Inicializa SDL.
	SDL_Init(SDL_INIT_EVERYTHING);

	// Crea la ventana con...
	window = SDL_CreateWindow("Super Mario Bros 1", // Nombre.
		SDL_WINDOWPOS_CENTERED, // Posición en X.
		SDL_WINDOWPOS_CENTERED, // Posición en Y.
		WIN_WIDTH, // Anchura.
		WIN_HEIGHT, // Altura.
		SDL_WINDOW_SHOWN); // Permitiendo su visibilidad.

	// Crea el render con...
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Pone el color del fondo.
	SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);

	// Por si falla la carga de la ventana y el render.
	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;
}

void Game::createTilemap() {
	std::ifstream entradaCSV(textureRoot + "maps/world1.csv");
	if (!entradaCSV.is_open()) {
		std::cout << "No se ha podido leer el archivo world1";
	}

	tileMap = new TileMap(entradaCSV, this);

	entradaCSV.close();
}

void Game::createEntitymap() {

	std::ifstream entradaTXT(textureRoot + "maps/world1.txt");

	if (!entradaTXT.is_open()) {
		std::cout << "No se ha podido leer el archivo world1";
	}

	// Leemos el mapa línea a línea para evitar acarreo de errores y permitir extensiones del formato
	std::string line;
	getline(entradaTXT, line);


	while (entradaTXT) {
		// Usamos un stringstream para leer la línea como si fuera un flujo
		stringstream lineStream(line);

		char tipo;
		lineStream >> tipo;

		switch (tipo) {
		case 'M':
			if (player == nullptr) {
				player = new Player(this, lineStream);
			}
			break;
			// uno para cada objeto
		case 'G':
			this->goombas.push_back(new Goomba(this, lineStream));

			break;
		case 'B':
			this->blocks.push_back(new Blocks(this, lineStream));
			
			break;
		case 'K':
			this->koopas.push_back( new Koopa(this, lineStream));
			break;
		}

		getline(entradaTXT, line);

	}
	entradaTXT.close();
}

void Game::deleteObj() {
	// Eliminar los obstaculos
	for (Goomba* g : goombas)
		delete g;
	goombas.clear();

	for (Koopa* k : koopas)
		delete k;
	koopas.clear();

	for (Blocks* s : blocks)
		delete s;
	blocks.clear();

	for (Mushroom* m : mushrooms)
		delete m;
	mushrooms.clear();
}

void Game::resetLevel() {

	player->resetPos();
	reset = true;
	deleteObj(); //eleminar los vectores de elemetos antes de leer otra vez
	createEntitymap();
	mapOffset = 0;
}

void Game::renderBlocks() const{
	for (int i = 0; i < blocks.size(); ++i) {
		blocks[i]->render(renderer);
	}
}
void Game::renderGoombas() const{
	for (int i = 0; i < goombas.size(); ++i) { // no he contado cuantos hay en total
		goombas[i]->render(renderer);
	}
}
void Game::renderMushroom() const {
	for (int i = 0; i < mushrooms.size(); ++i) { // no he contado cuantos hay en total
		mushrooms[i]->render(renderer);
	}
}

void Game::updateMushroom() const {
	for (int i = 0; i < mushrooms.size(); ++i) { // no he contado cuantos hay en total
		mushrooms[i]->update();
	}
}

void Game::renderKoopas() const {
	for (int i = 0; i < koopas.size(); ++i) {
		koopas[i]->render(renderer);
	}
}
void Game::updateKoopas() const {
	for (int i = 0; i < koopas.size(); ++i) {
		koopas[i]->update();
	}
}
void Game::updateGoombas() const {
	for (int i = 0; i < goombas.size(); ++i) {
		goombas[i]->update();
	}
}
void Game::updateBlocks() const {
	for (int i = 0; i < blocks.size(); ++i) {
		blocks[i]->update();
	}
}

void Game::ActMapOffset() {

	int posP = player->getPlayerPos().GetX() * TILE_SIDE;
	int mitadPantalla = (WIN_WIDTH / 2) + mapOffset;
	if (posP > mitadPantalla) {
		// Si el jugador está a la derecha del centro, desplazamos el mapa a la izquierda
		mapOffset += posP - mitadPantalla;
	}


}
#pragma endregion

// DESTRUCTORA.
Game::~Game()
{
	// Elimina los objetos del juego
	//delete perro;
	delete player;
	deleteObj();
	// Elimina las texturas.
	for (Texture* texture : textures) 
		delete texture;

	// Desactiva la SDL.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// BUCLE PRINCIPAL.
void Game::run()
{
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteraciÃ³n
		uint32_t inicio = SDL_GetTicks();

		update();       // Actualiza el estado de los objetos del juego
		
		if (!reset) {
			render();         // Dibuja los objetos en la venta
			handleEvents();   // Maneja los eventos de la SDL
		}
		
		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duración del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

int Game::getPlayerDirectionY() const {
	return this->player->getPlayerDir().GetY();
}

// RENDER.
void Game::render() const
{
	// Se limpia la pantalla.
	SDL_RenderClear(renderer);

	// Pinta los objetos del juego.
	tileMap->render();
	player->render(renderer);
	renderGoombas();
	renderKoopas();
	renderBlocks();
	renderMushroom();

	// Muestra todo lo renderizado.
	SDL_RenderPresent(renderer);
}


Collision::collision Game::checkCollision(const SDL_Rect& rect, bool fromPlayer) {

	Collision::collision result;// por defecto los booleanos estan falsos todos

	//colision con los bloques
	if (!result.collides) {
		int i = 0;
		while (i < blocks.size() && !result.collides) {
			result = blocks[i]->hit( rect, fromPlayer);
			if (!result.collides) ++i;
		}
	}
	if (!result.collides) {
		int i = 0;
		while (i < goombas.size() && !result.collides) {
			if (!goombas[i]->getFrozen()) result = goombas[i]->hit(rect, fromPlayer);
			if (!result.collides) ++i;
		}
	}
	if (!result.collides) {
		int i = 0;
		while (i < koopas.size() && !result.collides) {
			if (!koopas[i]->getFrozen()) result = koopas[i]->hit(rect, fromPlayer);
			if (!result.collides) ++i;
		}
	}
	if (!result.collides) {
		int i = 0;
		/*while (i < mushrooms.size() && !result.collides) {
			mushrooms[i]->hit(result, rect, fromPlayer);
			if (!result.collides) ++i;
		}*/
	}
	if (!result.collides) result = tileMap->hit(rect, fromPlayer);
	return result;


	//Collision::collision colTilemap = tileMap->hit(rect, fromPlayer); // Tilemap.
	//if (colTilemap.collides) return colTilemap;

	//// Goombas.
	//int i = 0;
	//bool found = false;
	//while (i < goombas.size() && !found) 
	//{
	//	Collision::collision colGoomba = goombas[i]->hit(rect, fromPlayer);
	//	if (colGoomba.collides) {
	//		found = true;
	//		return colGoomba;
	//	}
	//	i++;
	//}

	//// Bloques.
	//i = 0;
	//found = false;
	//while (i < blocks.size() && !found)
	//{
	//	Collision::collision colBlock = blocks[i]->hit(rect, fromPlayer);
	//	if (colBlock.collides) {
	//		found = true;
	//		return colBlock;
	//	}
	//	i++;
	//}

	//// Koopas.
	//i = 0;
	//found = false;
	//while (i < koopas.size() && !found)
	//{
	//	Collision::collision colKoopas = koopas[i]->hit(rect, fromPlayer);
	//	if (colKoopas.collides) {
	//		found = true;
	//		return colKoopas;
	//	}
	//	i++;
	//}

	//// Sin colisión.
	//return { false, false, SDL_Rect{0,0,0,0} };
	//
}

void Game::update()
{
	player->update();

	if (!reset) {
		// Actualiza los objetos del juego
		tileMap->update();

		updateGoombas();


		updateBlocks();

		updateKoopas();

		ActMapOffset();


		//eliminar los enemigos desaparecidos
		for (int i = 0; i < goombas.size(); ++i) {
			if (!goombas[i]->getDead()) {
				goombas[i] = goombas.back();
				goombas.pop_back();
			}
		}
		for (int i = 0; i < koopas.size(); ++i) {
			if (!koopas[i]->getDead()) {
				koopas[i] = koopas.back();
				koopas.pop_back();
			}
		}

		//eliminar los bloques destruidos por supermario
		for (int i = 0; i < blocks.size(); ++i) {
			if (blocks[i]->getDestroyed()) {
				blocks[i] = blocks.back();
				blocks.pop_back();
			}
		}
		for (int i = 0; i < mushrooms.size(); ++i) {
			/*if (mushrooms[i]->hasBeenEaten()) {
				mushrooms[i] = mushrooms.back();
				mushrooms.pop_back();
			}*/
		}
	}
}

void Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN) {

			switch (evento.key.keysym.sym) {
				//movimineto del player
			case SDLK_LEFT:
			case SDLK_RIGHT:
			case SDLK_SPACE:
				player->handleEvent(evento);
				break;
			}
		}
		else if (evento.type == SDL_KEYUP) {
			switch (evento.key.keysym.sym) {
			case SDLK_LEFT:
			case SDLK_RIGHT:
			case SDLK_SPACE:
				player->handleEvent(evento);
				break;
			}
		}
	}
}


