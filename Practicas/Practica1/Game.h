#pragma once

// Biblioteca estándar de C++.
#include <array>
#include <fstream>
#include <iostream>

// Biblioteca SDL.
#include <SDL.h>

// Nuestras clases
#include <vector>
#include "Texture.h"
#include "Player.h"
#include "TileMap.h"  // Ensure this is in place and correct

#include "Goomba.h"
#include "Blocks.h"
//#include "Dog.h"

using uint = unsigned int;
class TileMap; 
class Player;
class Goomba;
class Blocks;

class Game {
public:
    // Identificadores de las texturas
    enum TextureName {
        // De momento nada. Aquí irán Mario, Koopa...
        BACKGROUND,
        MARIO,
        SUPERMARIO,
        GOOMBA,
        BLOCKS,
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

    // Lleva la coordenada x del extremo izquierdo de la vista.
    int mapOffset;
    int mapMove;

    // Objetos del juego
    TileMap* tileMap;
    Player* player;
    std::array <Goomba*, 20> goombas;
    std::array <Blocks*, 70> blocks;

    //std::vector<Goomba*> enemies;
    //std::vector<Block*> blocks;

    // --- MÉTODOS AUXILIARES ---.
    // Constructora.
    void createSDL();
    void createTextures();
    void createTilemap();
    void createEntitymap();
    void renderBlocks() const;
    void renderGoombas() const;

public:

    Game();
    void loadObjectMap(std::ifstream&);
    void run();
    void update();
    void render() const;
    void handleEvents();
    Texture* getTexture(TextureName) const;
    //void LoadMap();

    // Constante globales

    static constexpr int TILE_SIDE = 32;
    static constexpr int WIN_TILE_WIDTH = 18;
    static constexpr int WIN_TILE_HEIGHT = 16;
    static constexpr int WIN_WIDTH = TILE_SIDE* WIN_TILE_WIDTH;
    static constexpr int WIN_HEIGHT = TILE_SIDE * WIN_TILE_HEIGHT;
    static constexpr int FRAME_RATE = 50;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = NOW;
    double deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

    int getMapOffset() { return mapOffset; }
    void setMapOffset(int e) { mapOffset = e; }

    ~Game();
};