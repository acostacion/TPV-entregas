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
};
#pragma endregion

// CONSTRUCTORA.
Game::Game() : seguir(true){
	// --- SDL ---.
	createSDL();

	// --- TEXTURAS ---.
	createTextures();

	mapOffset = 0;

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
			this->player = new Player(this, lineStream);
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


void Game::renderBlocks() const{
	for (int i = 0; i < blocks.size(); ++i) {
		blocks[i]->render();
	}
}
void Game::renderGoombas() const{
	for (int i = 0; i < goombas.size(); ++i) { // no he contado cuantos hay en total
		goombas[i]->render();
	}
}
void Game::renderKoopas() const {
	for (int i = 0; i < koopas.size(); ++i) {
		koopas[i]->render();
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
	renderGoombas();
	renderKoopas();
	renderBlocks();

	// Muestra todo lo renderizado.
	SDL_RenderPresent(renderer);
}

Texture* Game::getTexture(TextureName name) const {
	return textures[name];
}

Collision::collision Game::checkCollision(const SDL_Rect& rect, bool fromPlayer) {
	Collision::collision col = tileMap->hit(rect, fromPlayer);

	if (fromPlayer) { // si es el player
		
	}
	else { // si es enemigo

	}


	// Itera sobre los objeto del juego llamando a sus métodos hit. Si alguno devuelve que ha habido colisión, interrumpe la búsqueda y devuelve ese resultado.
	/*
	// pregunta al hit de todas las entidades del juego, si se colisiona con alguna
	// todos con el tilemap
	// player -> goomba (si es por la der o iz -vida, por arriba muerte de goomba)
	// player -> koopa (si es por la der o iz -vida, por arriba "muerte" de koopa)
	// player -> seta (super mario y muerte/desaparece seta)
	// player -> blocks -> ladrillo(no avanza si es por abajo der iz), "?" se vuelve vacio, vacio nada
	// playerSUPER -> blocks -> ladrillo(destruye), "?" se vuelve vacio
	// 
	// entities chocan con entities

	// Enemigo, bloque, player.
	Collision colision = { false, false, false };
	
	//  --- ENEMIGOS ---.
	//if (blocks)


		return colision;*/


	

	return col;
}





void Game::update()
{
	// Actualiza los objetos del juego
	tileMap->update();

	updateGoombas();

	player->update();

	updateBlocks();

	updateKoopas();

	// Si la posición del player supera la mitad, avanza (corregir).
	if (player->getX() > WIN_TILE_WIDTH/2 -1 && player->getMovingDer()) {
		mapOffset += sumMapOffset;
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



