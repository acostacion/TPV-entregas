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
Game::Game() : gameContinue(true), mapOffset(0), reset(false), wonGame(false) {
	try {
		// --- SDL ---.
		createSDL();

		// --- TEXTURAS ---.
		createTextures();

		Smario = false;

		// --- MAPAS ---.
		createTilemap();
		createEntitymap();
	}
	catch(...){
		std::cout << "Error creando Game.";
	}
}

#pragma region Submétodos Constructora
void Game::createTextures() {
	try {
		for (int i = 0; i < NUM_TEXTURES; ++i) {
			// Crea las texturas...
			textures[i] = new Texture(renderer,
				(textureRoot + textureSpec[i].name).c_str(), // Dirección.
				textureSpec[i].numRows, // Filas.
				textureSpec[i].numColumns); // Columnas
		}
	}
	catch (...) {
		std::cout << "Error creando las texturas.";
	}
	
}

void Game::createSDL() {
	try {
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
			throw "Error cargando ventana o render"s;
	}
	catch (...) {
		std::cout << "Error creando SDL.";
	}
	
}

void Game::createTilemap() {
	try {
		std::ifstream entradaCSV(textureRoot + "maps/world1.csv");
		if (!entradaCSV.is_open()) {
			throw "No se ha podido leer el archivo world1"s;
		}

		tileMap = new TileMap(entradaCSV, this);
		entradaCSV.close();
	}
	catch (...) {
		std::cout << "Error creando el tilemap.";
	}
	
}

void Game::createEntitymap() {

	try {
		std::ifstream entradaTXT(textureRoot + "maps/world1.txt");

		if (!entradaTXT.is_open()) {
			std::cout << "No se ha podido leer el archivo world1";
		}

		// Leemos el mapa línea a línea para evitar acarreo de errores y permitir extensiones del formato
		std::string line;
		std::getline(entradaTXT, line);


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
				this->koopas.push_back(new Koopa(this, lineStream));
				break;
			}

			std::getline(entradaTXT, line);
	}
		entradaTXT.close();

	}
	catch (...) {
		std::cout << "Error creando el entitymap.";
	}
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
	deleteObj(); //eleminar los vectores 
	createEntitymap();
	mapOffset = 0;
}

void Game::renderEntities()const {
	// BLOCKS.
	for (int i = 0; i < blocks.size(); ++i) {
		blocks[i]->render(renderer);
	}

	// GOOMBAS.
	for (int i = 0; i < goombas.size(); ++i) { // no he contado cuantos hay en total
		goombas[i]->render(renderer);
	}

	// MUSHROOMS.
	for (int i = 0; i < mushrooms.size(); ++i) { 
		mushrooms[i]->render(renderer);
	}

	// KOOPAS.
	for (int i = 0; i < koopas.size(); ++i) {
		koopas[i]->render(renderer);
	}
}
void Game::updateEntities()const {
	// MUSHROOMS.
	for (int i = 0; i < mushrooms.size(); ++i) {
		mushrooms[i]->update();
	}

	// KOOPAS.
	for (int i = 0; i < koopas.size(); ++i) {
		koopas[i]->update();
	}

	// GOOMBAS.
	for (int i = 0; i < goombas.size(); ++i) {
		goombas[i]->update();
	}

	// BLOCKS.
	for (int i = 0; i < blocks.size(); ++i) {
		blocks[i]->update();
	}
}
void Game::deleteEntities() {
	// ELIMINAR GOOMBAS.
	for (int i = 0; i < goombas.size(); ++i) {
		if (goombas[i]->isDead()) {
			delete goombas[i];
			goombas[i] = goombas.back();
			goombas.pop_back();
		}
	}

	// ELIMINAR KOOPAS
	for (int i = 0; i < koopas.size(); ++i) {
		if (!koopas[i]->isAlive()) {
			delete koopas[i];
			koopas[i] = koopas.back();
			koopas.pop_back();
		}
	}

	// ELIMINAR BLOQUES
	for (int i = 0; i < blocks.size(); ++i) {
		if (blocks[i]->getDestroyed()) {
			delete blocks[i];
			blocks[i] = blocks.back();
			blocks.pop_back();
		}
	}

	// ELIMINAR SETAS.
	for (int i = 0; i < mushrooms.size(); ++i) {
  		if (mushrooms[i]->isDead()) {
			delete mushrooms[i];
			mushrooms[i] = mushrooms.back();
			mushrooms.pop_back();
		}
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
	while (gameContinue) {
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
	renderEntities();

	// Muestra todo lo renderizado.
	SDL_RenderPresent(renderer);
}



Collision::collision Game::checkCollision(const SDL_Rect& rect, bool fromPlayer) {

	Collision::collision result;// por defecto los booleanos estan falsos todos
	// Verificar colisión con bloques
	//if (!result.collides) {
		for (auto& block : blocks) {
			result = block->hit(rect, fromPlayer);
			if (result.collides) break;
		}
	

	// Verificar colisión con goombas
	if (!result.collides) {
		for (auto& goomba : goombas) {
			if (!goomba->getFrozen()) {
				result = goomba->hit(rect, fromPlayer);
				if (result.collides) break;
			}
		}
	}

	// Verificar colisión con koopas
	if (!result.collides) {
		for (auto& koopa : koopas) {
			if (!koopa->getFrozen()) {
				result = koopa->hit(rect, fromPlayer);
				if (result.collides) break;
			}
		}
	}

	// Verificar colisión con hongos
	if (!result.collides) {
		for (auto& mushroom : mushrooms) {
			result = mushroom->hit(rect, fromPlayer);
			if (result.collides) break;
		}
	}

	// Verificar colisión con el fondo
	if (!result.collides) {
		result = tileMap->hit(rect, fromPlayer);
	}
	

	return result;

}

void Game::update()
{
	player->update();

	if (!reset) {
		// Actualiza los objetos del juego
		tileMap->update();

		updateEntities();

		ActMapOffset();

		// ELIMINAR PLAYER.
		if (player->isDead()) {
			delete player;
			end();
		}
		if (player->getPlayerPos().GetX() == WIN_WIDTH * TILE_SIDE * 20) {
			wonGame = true;
			end();
		}
		deleteEntities();
	}
}


void Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			gameContinue = false;
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


