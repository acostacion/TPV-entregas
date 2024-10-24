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

//#include "Goomba.h"
//#include "Block.h"
//#include "Dog.h"

using uint = unsigned int;
class TileMap; 
class Player;

class Game {
public:
    // Identificadores de las texturas
    enum TextureName {
        // De momento nada. Aquí irán Mario, Koopa...
        BACKGROUND,
        MARIO,
        SUPERMARIO,
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
    Player* player;
    //std::vector<Goomba*> enemies;
    //std::vector<Block*> blocks;

public:
    void loadObjectMap();
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

    int getMapOffset() { return mapOffset; }

    Game();
    ~Game();
};