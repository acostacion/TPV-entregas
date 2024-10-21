#pragma once

// Biblioteca estándar de C++.
#include <array>

// Biblioteca SDL.
#include <SDL.h>

// Nuestras clases
#include "Texture.h"
#include <vector>
#include "Texture.h"
//#include "Player.h"
#include "TileMap.h"
//#include "Goomba.h"
//#include "Block.h"
//#include "Dog.h"

using uint = unsigned int;

//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		// De momento nada. Aquí irán Mario, Koopa...
		BACKGROUND,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Interruptor para terminar el juego
	bool seguir;

	int mapOffset;

	// Objetos del juego
	TileMap* tileMap;

	//Player* player;
	//std::vector<Goomba*> enemies;
	//std::vector<Block*> blocks;


public:
	void run();

	//void update();
	void render() const;
	//void handleEvents();

	Texture* getTexture(TextureName name) const;

	//void LoadMap();

	// Constante globales
	static constexpr uint WIN_WIDTH = 800;
	static constexpr uint WIN_HEIGHT = 600;
	static constexpr uint FRAME_RATE = 50;

	int getMapOffset() { return mapOffset; }

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}