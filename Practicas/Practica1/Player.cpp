#include "Player.h"
#include <algorithm>

Player::Player(Game* game, std::istream& in) : game(game), flip(SDL_FLIP_NONE)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	in >> life; // el n�mero de vidas
	dir = Point2D<float>(0,0);
	superMario = false;
    anim = 0;
    movingDer = false;
    moving = false;
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


    // 3. Frame de la animacion

    if (!isGrounded) anim = 6;
    else {
        if (moving) {
            if (anim == 0) anim = 2;
            else if (anim == 2) anim = 3;
            else if (anim == 3) anim = 4;
            else if (anim == 4) anim = 0;
            else if (anim == 6) anim = 0;
        }
        else anim = 0;
      
    }
    

	// Se renderiza.
	texturaMario->renderFrame(rect, 0, anim, flip);
}

// Input de teclado cambian la dir del jugador.
void Player::handleEvent(SDL_Event evento) {
    Point2D<float> nuevaDir = dir;
    movingDer = false;
    
    // Escanea la tecla.
    SDL_Scancode tecla = evento.key.keysym.scancode;


    // Al pulsar la tecla...
    if (evento.type == SDL_KEYDOWN) {
        if ((tecla == SDL_SCANCODE_W || tecla == SDL_SCANCODE_SPACE || tecla == SDL_SCANCODE_UP) && isGrounded) {
            nuevaDir = Point2D<float>(dir.GetX(), JUMP_FORCE);
            if (dir.GetX() > 0) movingDer = true;
            isGrounded = false; 
        }
        else if (tecla == SDL_SCANCODE_A || tecla == SDL_SCANCODE_LEFT) {
            nuevaDir = Point2D<float>(-MOVE_SPEED, dir.GetY());
            flip = SDL_FLIP_HORIZONTAL;
        }
        else if (tecla == SDL_SCANCODE_S || tecla == SDL_SCANCODE_DOWN) {
            // Mario nunca va abajo, pero se pone la animacion de agacharse.
        }
        else if (tecla == SDL_SCANCODE_D || tecla == SDL_SCANCODE_RIGHT) {
            nuevaDir = Point2D<float>(MOVE_SPEED, dir.GetY());
            movingDer = true;
            flip = SDL_FLIP_NONE;
            
        }
        moving = true;
    }
    // Al despulsar la tecla...
    else if (evento.type == SDL_KEYUP) {
        if (tecla == SDL_SCANCODE_A || tecla == SDL_SCANCODE_LEFT || tecla == SDL_SCANCODE_D || tecla == SDL_SCANCODE_RIGHT) {
            nuevaDir = Point2D<float>(dir.GetX() * 0.2, dir.GetY()); // Reduce speed slightly for sliding effect 
            moving = false;
        }
    }
    dir = nuevaDir;
}

void Player::update() {

    //gravedad
    if (!isGrounded) {
        dir = Point2D<float>(dir.GetX(), dir.GetY() + GRAVITY);
        if (dir.GetY() > MAX_FALL_SPEED) {
            dir = Point2D<float>(dir.GetX(), MAX_FALL_SPEED);
        }
    }

    if (pos.GetY() >= Game::WIN_TILE_HEIGHT - 3) { // por ahora
        pos = Point2D<float>(pos.GetX(), Game::WIN_TILE_HEIGHT - 3);
        isGrounded = true;
        dir = { dir.GetX(), 0 };
    }

    // patinar
    if (!moving) {
        if (std::abs(dir.GetX()) < DECELERATION) {
            dir = Point2D<float>(0, dir.GetY());
        }
        else {
            dir = Point2D<float>(dir.GetX() * 0.8, dir.GetY());
        }
    }
    
   

    pos = Point2D<float>(pos.GetX() + dir.GetX(), pos.GetY() + dir.GetY());

    // CON ESTO SE MUEVE DE IZQUIERDA A DERECHA.



    if (pos.GetX() < 0) { // no se vaya por la izquierda
        pos = Point2D<float>(0, pos.GetY()); 
    } 
    else if (pos.GetX() > Game::WIN_TILE_WIDTH/2) // no pase de la mitad
    {
        pos = Point2D<float>(game->WIN_TILE_WIDTH /2, pos.GetY());
    }


}