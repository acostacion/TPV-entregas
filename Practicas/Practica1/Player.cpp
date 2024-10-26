#include "Player.h"


Player::Player(Game* game, std::istream& in) : game(game)
{
	in >> pos; // ser� in Point2D que sabe leerse
	pos = pos - Point2D<float>(0, 1);
	in >> life; // el n�mero de vidas
	dir = Point2D<float>(0,0);
	superMario = false;

    jumping = false;
    onGround = true;

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
    if (evento.type == SDL_KEYDOWN) {
        switch (evento.key.keysym.sym) {
        case SDLK_LEFT:
            nuevaDir = Point2D<float>(-0.1, 0);
           
            break;
        case SDLK_RIGHT:
            nuevaDir = Point2D<float>(0.1, 0);
            break;
        case SDLK_SPACE:
            if (onGround) {  
                nuevaDir = Point2D<float>(dir.GetX(), JUMP_FORCE);
                onGround = false;
            }
            break;
        default:
            break;
        }
    }
    else if (evento.type == SDL_KEYUP) {
        switch (evento.key.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_RIGHT:
            nuevaDir = Point2D<float>(0, dir.GetY()); // Stop horizontal movement
            break;
        default:
            break;
        }
    }
    dir = nuevaDir;
}

void Player::update() {

    Point2D<float> nuevadir(dir.GetX(), dir.GetY() + GRAVITY);

    if (!onGround) { // gravedad
        if (dir.GetY() > MAX_FALL_SPEED) nuevadir = Point2D<float>(nuevadir.GetX(), MAX_FALL_SPEED); // Clamp fall speed
        dir = nuevadir;

    }

    
    if (dir.GetX() > 0) nuevadir = Point2D<float>(std::max(0.0f, dir.GetX() - ACCELERATION / 2), dir.GetY());
    else if (dir.GetX() < 0) nuevadir = Point2D<float>(std::min(0.0f, dir.GetX() + ACCELERATION / 2), dir.GetY());

    
    pos = pos + dir;

    
    
    
}