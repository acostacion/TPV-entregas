#include "CheckML.h"
#include "Game.h"

#include <string>
#include <sstream>


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
	TextureSpec{"images/background.png", 9, 7}, 
	TextureSpec{"images/mario.png", 12, 1}, 
	TextureSpec{"images/supermario.png", 22, 1},
	TextureSpec{"images/goomba.png", 3, 1},
	TextureSpec{"images/blocks.png", 6, 1},
	TextureSpec{"images/koopa.png", 4, 1},
	TextureSpec{"images/mushroom.png", 1, 1},
	TextureSpec{"images/coin.png", 1, 1},
	TextureSpec{"images/firemario.png", 21, 1},
	TextureSpec{"images/shell.png", 2, 1},
	TextureSpec{"images/star.png", 4, 1},
	TextureSpec{"images/lift.png", 1, 1},
	TextureSpec{"images/piranha.png", 1, 1}
};
#pragma endregion

// CONSTRUCTORA.
Game::Game() : gameContinue(true), mapOffset(0), reset(false), wonGame(false) {
	try {
		// --- SDL ---.
		createSDL();

		// --- TEXTURAS ---.
		createTextures();

		totalPoints = 0;
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

		tileMap = new TileMap(this, entradaCSV);
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
				//this->sceneObjects.push_back(new Goomba(this, lineStream));

				break;
			case 'B':
				//this->sceneObjects.push_back(new Blocks(this, lineStream));

				break;
			case 'K':
				//this->sceneObjects.push_back(new Koopa(this, lineStream));
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


void Game::resetLevel() {
	player->resetPos();
	deleteObj(); //eleminar los vectores 
	createEntitymap();
	mapOffset = 0;
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
	delete tileMap;
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

	for (auto& obj : sceneObjects) obj->render();

	// Muestra todo lo renderizado.
	SDL_RenderPresent(renderer);
}



Collision::collision Game::checkCollision(const SDL_Rect& rect, bool fromPlayer) {

	Collision::collision result;// por defecto los booleanos estan falsos todos
	// Verificar colisión con bloques
	//if (!result.collides) {
	
	return result;
}

void Game::update()
{
	player->update();

	if (!reset) {
		// Actualiza los objetos del juego

		for (auto& obj : sceneObjects) obj->update();

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


