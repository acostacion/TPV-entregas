#pragma once

// Biblioteca estándar de C++.
#include <array>
#include <fstream>
#include <iostream>

// Biblioteca SDL.
#include <SDL.h>

// Nuestras clases.
#include <vector>
#include "Texture.h"
#include "Player.h"
#include "TileMap.h"  
#include "Goomba.h"
#include "Koopa.h"
#include "Blocks.h"
#include "Collision.h"



using uint = unsigned int;
class TileMap; 
class Player;
class Goomba;
class Koopa;
class Blocks;
class Mushroom;

class Game {
public:
    // Identificadores de las texturas
    enum TextureName {
        BACKGROUND,
        MARIO,
        SUPERMARIO,
        GOOMBA,
        BLOCKS,
        KOOPA,
        MUSHROOM,
        NUM_TEXTURES,  // Truco C++: número de texturas definidas
    };

private:
    
    SDL_Window* window = nullptr; // Ventana de la SDL (se destruirá en el destructor)
    SDL_Renderer* renderer = nullptr; // Renderizador de la SDL (para dibujar)
    std::array<Texture*, NUM_TEXTURES> textures; // Array con todas las texturas del juego
    bool gameContinue; // Interruptor para terminar el juego
    bool wonGame; // Ganar
    int mapOffset; // Lleva la coordenada x del extremo izquierdo de la vista.
    int sumMapOffset = 1;

    bool Smario = false;
    bool reset;
    // Objetos del juego
    TileMap* tileMap;
    Player* player = nullptr;

    std::vector<Goomba*> goombas;
    std::vector<Blocks*> blocks;
    std::vector<Koopa*> koopas;
    std::vector<Mushroom*> mushrooms;

    // --- MÉTODOS AUXILIARES ---.
    // Constructora.
    void createSDL();
    void createTextures();
    void createTilemap();
    void createEntitymap();

    void renderEntities()const;
    void updateEntities()const;
    void deleteEntities();

    void ActMapOffset();
    void deleteObj();

    // Colisiones.
   
    

public:

    Game();
    ~Game();

    void run();
    void update();
    void render() const;
    void handleEvents();
    void resetLevel();
    void end();
    bool won() const {
        return wonGame;
    };
    Collision::collision checkCollision(const SDL_Rect&, bool);
    
    Texture* getTexture(TextureName) const;
    int getMapOffset() const;
    int getPlayerDirectionY() const;
    void addMushroom(Mushroom* n);
    void setMapOffset(int e) { mapOffset = e; }
    bool getSMario() { return Smario; }
    SDL_Renderer* getRender() { return renderer; }
  
    void ChangeMario() {
        Smario = !Smario;
    }
    // Constante globales
    static constexpr int TILE_SIDE = 32;
    static constexpr int WIN_TILE_WIDTH = 18;
    static constexpr int WIN_TILE_HEIGHT = 16;
    static constexpr int WIN_WIDTH = TILE_SIDE* WIN_TILE_WIDTH;
    static constexpr int WIN_HEIGHT = TILE_SIDE * WIN_TILE_HEIGHT;
    static constexpr int FRAME_RATE = 50;
    static constexpr bool DEBUG = true;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = NOW;
    double deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
  
};


inline Texture*
Game::getTexture(TextureName name) const
{
    return textures[name];
}
inline int
Game::getMapOffset() const {
    return mapOffset;
}


inline void
Game::addMushroom(Mushroom* n) {
    mushrooms.push_back(n);
}
inline void
Game::end() {
    gameContinue = false;
}

