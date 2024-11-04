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

    collision.h = texturaMario->getFrameHeight();
    collision.w = texturaMario->getFrameWidth();
    collision.x = pos.GetX();
    collision.y = pos.GetY();

}

SDL_Rect Player::createRect(int w, int h, int x, int y) {
    // Se crea el rect.
    SDL_Rect rect;

    // Se le da dimensiones y posición.
    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;

    return rect;
}

void Player::render() {
	
	/*/if (!this->superMario) {*/

    SDL_Rect renderRect = createRect(texturaMario->getFrameWidth(), // w.
                                     texturaMario->getFrameHeight(),  // h.
                                     pos.GetX() * Game::TILE_SIDE,  // x.
                                     pos.GetY() * Game::TILE_SIDE); // y.

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
	texturaMario->renderFrame(renderRect, 0, anim, flip);
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

    pos = Point2D<float>(pos.GetX() + dir.GetX(), pos.GetY() + dir.GetY());

    if (dir.GetX() > 0) { // si va a la derecha
        collision.x = pos.GetX() + COLLISION_OFFSET;
    }
    else { // si va a la izquierda
        collision.x = pos.GetX() - COLLISION_OFFSET;
    }


    if (dir.GetY() > 0) {// si va hacia arriba
        collision.y = pos.GetY() - COLLISION_OFFSET;

    }
    else {// si va hacia abajo
        collision.y = pos.GetY() + COLLISION_OFFSET;
    }


    collisionRes = game->checkCollision(collision, true);
    if (collisionRes.collides) {
        hit(collisionRes.intersectRect);
    }

    //if (pos.GetY() >= Game::WIN_TILE_HEIGHT - 3) { // por ahora
    //    pos = Point2D<float>(pos.GetX(), Game::WIN_TILE_HEIGHT - 3);
    //    isGrounded = true;
    //    dir = { dir.GetX(), 0 };
    //}

    // patinar
    if (!moving) {
        if (std::abs(dir.GetX()) < DECELERATION) {
            dir = Point2D<float>(0, dir.GetY());
        }
        else {
            dir = Point2D<float>(dir.GetX() * 0.8, dir.GetY());
        }
    }
    // CON ESTO SE MUEVE DE IZQUIERDA A DERECHA.

    if (pos.GetX() < 0) { // no se vaya por la izquierda
        pos = Point2D<float>(0, pos.GetY()); 
    } 
    else if (pos.GetX() > Game::WIN_TILE_WIDTH/2) // no pase de la mitad
    {
        pos = Point2D<float>(game->WIN_TILE_WIDTH /2, pos.GetY());
    }


}

Collision::collision Player::hit(const SDL_Rect otherRect) {
    Collision::collision resultadoFinal ;
    SDL_Rect result = createRect(0, 0, 0, 0);
   
    SDL_IntersectRect(&collisionRes.intersectRect, &collision, &result);
    SDL_bool haColisionado= SDL_HasIntersection(&collisionRes.intersectRect, &collision);
    if (haColisionado) {

    }


    return resultadoFinal;
}