#include "Player.h"


Player::Player(Game* game, std::istream& in) : game(game)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	in >> life; // el n�mero de vidas
	dir = Point2D<float>(0,0);
	superMario = false;

    jumping = false;
    isGrounded = true;

	texturaMario = game->getTexture(Game::MARIO);
	texturaSMario = game->getTexture(Game::SUPERMARIO);
}

void Player::render() {
	
	/*/if (!this->superMario) {*/

	// 1. Se crea el rect.
	SDL_Rect rect;

	// 2. Se le da dimensiones y posici�n.
	rect.w = texturaMario->getFrameWidth();
	rect.h = texturaMario->getFrameHeight();
	rect.x = pos.GetX() * Game::TILE_SIDE;
	rect.y = pos.GetY() * Game::TILE_SIDE;

	// Se renderiza.
	texturaMario->renderFrame(rect, 0, 0);
}

// Input de teclado cambian la dir del jugador.
void Player::handleEvent(SDL_Event evento) {
    Point2D<float> nuevaDir;

    // Escanea la tecla.
    SDL_Scancode tecla = evento.key.keysym.scancode;


    // Al pulsar la tecla...
    if (evento.type == SDL_KEYDOWN) {
        if (tecla == SDL_SCANCODE_W || tecla == SDL_SCANCODE_SPACE || tecla == SDL_SCANCODE_UP) {
            nuevaDir = Point2D<float>(0, -1);
        }
        else if (tecla == SDL_SCANCODE_A || tecla == SDL_SCANCODE_LEFT) {
            nuevaDir = Point2D<float>(-1, 0);
        }
        else if (tecla == SDL_SCANCODE_S || tecla == SDL_SCANCODE_DOWN) {
            // Mario nunca va abajo, pero se pone la animacion de agacharse.
        }
        else if (tecla == SDL_SCANCODE_D || tecla == SDL_SCANCODE_RIGHT) {
            nuevaDir = Point2D<float>(1, 0);
        }
    }
    // Al despulsar la tecla...
    else if (evento.type == SDL_KEYUP) {
        nuevaDir = Point2D<float>(0, 0);
    }
    dir = nuevaDir;
}

void Player::update() {

    /*Point2D<float> nuevadir(dir.GetX(), dir.GetY() + GRAVITY);

    if (!isGrounded) { // gravedad
        if (dir.GetY() > MAX_FALL_SPEED) nuevadir = Point2D<float>(nuevadir.GetX(), MAX_FALL_SPEED); // Clamp fall speed
        dir = nuevadir;

    }

    
    if (dir.GetX() > 0) nuevadir = Point2D<float>(std::max(0.0f, dir.GetX() - ACCELERATION / 2), dir.GetY());
    else if (dir.GetX() < 0) nuevadir = Point2D<float>(std::min(0.0f, dir.GetX() + ACCELERATION / 2), dir.GetY());

    
    pos = pos + dir;*/

    // Si "left" y "right" ocurren a la vez...
    if (dir.GetX() == -1 == dir.GetX() == 1) {
        dir = Point2D<float>(0, 0);
    }
    // Cualquier otro caso...
    else{
        if (dir.GetY() == -1 && isGrounded) { // W (estando en el suelo).
            isGrounded = false; 
            dir = Point2D<float>(0, 1);

        }
        else if (dir.GetX() == -1) { // A.
            pos = Point2D<float>(pos.GetX() + dir.GetX() * 2, 0);
        }
        else if(dir.GetX() == 1){ // D.
            pos = Point2D<float>(pos.GetX() + dir.GetX() * 2, 0);
        }
    }

    if (!isGrounded) {
        dir = Point2D<float>(0, pos.GetY() + dir.GetY() * 2);
    }
}