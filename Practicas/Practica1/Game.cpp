#include <string>
#include <sstream>
#include "Game.h"

using namespace std;

// Formato de la especificaci√≥n de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// N√∫mero de frames por cols
	uint numRows;		// N√∫mero de frames por fils
};

// Directorio ra√≠z de los archivos de textura
const string textureRoot = "../assets/";

// Especificaci√≥n de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"imgs/background.png", 9, 7}, // {Mapa, cols, fils}
	TextureSpec{"imgs/mario.png", 12, 1}, // {Mapa, cols, fils}
	TextureSpec{"imgs/supermario.png", 22, 1}, // {Mapa, cols, fils}
};


void Game::loadObjectMap(std::ifstream& entrada) {


	// Leemos el mapa lÌnea a lÌnea para evitar acarreo de errores
	// y permitir extensiones del formato
	std::string line;
	getline(entrada, line);

	while (entrada) {
		// Usamos un stringstream para leer la lÌnea como si fuera un flujo
		stringstream lineStream(line);

		char tipo;
		lineStream >> tipo;

		switch (tipo) {
		case 'M':
			this->player = new Player(this, lineStream);
			break;
			// uno para cada objeto
		}

		getline(entrada, line);

	}
}

Game::Game()
 : seguir(true)
{
	// Inicializa la SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL",
	                          SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED,
	                          WIN_WIDTH,
	                          WIN_HEIGHT,
	                          SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
		                          (textureRoot + textureSpec[i].name).c_str(),
		                          textureSpec[i].numRows,
					  textureSpec[i].numColumns);

	mapOffset = 0;


	// Crea los objetos del juego 

	std::ifstream entrada("../assets/maps/world1.csv");
	if (!entrada.is_open()) {
		std::cout << "No se ha podido leer el archivo world1";
	}

	tileMap = new TileMap(entrada, this);

	entrada.close();


	std::ifstream entrada2("../assets/maps/world1.txt");
	if (!entrada2.is_open()) {
		std::cout << "No se ha podido leer el archivo world1";
	}
	
	loadObjectMap(entrada2);

	entrada2.close();




	//perro = new Dog(this, -textures[BACKGROUND]->getFrameWidth(), 390);
}

Game::~Game()
{
	// Elimina los objetos del juego
	//delete perro;

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;



	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}





void
Game::run()
{
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteraci√≥n
		uint32_t inicio = SDL_GetTicks();

		update();       // Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraciÛn del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// Pinta los objetos del juego
	tileMap->Render();
	player->render();

	SDL_RenderPresent(renderer);
}


Texture* Game::getTexture(TextureName name) const {
	return textures[name];
}



void
Game::update()
{
	// Actualiza los objetos del juego
	tileMap->Update();
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN) {
			player->handleEvent(evento);
			++mapOffset;
		}
	}
}



