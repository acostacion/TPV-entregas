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
};
#pragma endregion

// CONSTRUCTORA.
Game::Game() : seguir(true){
	// --- SDL ---.
	createSDL();

	// --- TEXTURAS ---.
	createTextures();

	mapOffset = 0;
	mapMove = WIN_WIDTH / 2 -2;

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

	int g = 0, b = 0;
	while (entradaTXT) {
		// Usamos un stringstream para leer la línea como si fuera un flujo
		stringstream lineStream(line);

		char tipo;
		lineStream >> tipo;

		switch (tipo) {
		case 'M':
			this->player = new Player(this, lineStream);
			break;
			// uno para cada objeto
		case 'G':
			this->goombas[g] = new Goomba(this, lineStream);
			g++;
			break;
		case 'B':
			this->blocks[b] = new Blocks(this, lineStream);
			b++;
			break;
		}

		getline(entradaTXT, line);

	}
	entradaTXT.close();
}


void Game::renderBlocks() {
	for (int i = 0; i < blocks.size(); ++i) {
		blocks[i]->render();
	}
}

void Game::blocksMove() {
	for (int i = 0; i < blocks.size(); ++i) {
		blocks[i]->update();
	}
}

#pragma endregion

// DESTRUCTORA.
Game::~Game()
{
	// Elimina los objetos del juego
	//delete perro;

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
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duración del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}




// RENDER.
void Game::render() const
{
	// Se limpia la pantalla.
	SDL_RenderClear(renderer);

	// Pinta los objetos del juego.
	tileMap->render();
	player->render();
	goombas[0]->render();
	blocks[0]->render();

	// Muestra todo lo renderizado.
	SDL_RenderPresent(renderer);
}

Texture* Game::getTexture(TextureName name) const {
	return textures[name];
}

void Game::update()
{
	// Actualiza los objetos del juego
	tileMap->update();
	goombas[0]->update();
	player->update();
	// Si la posición del player supera la mitad, avanza (corregir).
	if (player->getX() > 8 && player->getMovingDer()) {
		mapOffset += 12;
		mapMove+= 12;
		blocksMove();
	}
}

void Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP) {
			player->handleEvent(evento);
		}
	}
}



