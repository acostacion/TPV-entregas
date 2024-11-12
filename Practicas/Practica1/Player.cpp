#include "Player.h"
#include <algorithm>

Player::Player(Game* game, std::istream& in) 
    : game(game), superMario(false), altura(0), isGrounded(false), isJumping(false), dir(DIR_INI)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1.5); // ajusta pos.
	in >> life; // vidas.

	texturaMario = game->getTexture(Game::MARIO);
	texturaSMario = game->getTexture(Game::SUPERMARIO);

    invulnerable = false;
    verticalVelocity = 0;


    posInicio = pos;
}

SDL_Rect Player::createRect(float x, float y) {
    // Se crea el rect.
    SDL_Rect rect;

    if (!superMario) { // MARIO.
        rect.w = texturaMario->getFrameWidth() - 8;
        rect.h = texturaMario->getFrameHeight();
    }
    else { // SUPER MARIO.
        rect.w = texturaSMario->getFrameWidth() - 8;
        rect.h = texturaSMario->getFrameHeight();
    }
    rect.x = x + 8;
    rect.y = y;

    return rect;
}

SDL_Rect Player::getRect(bool forRender) const {
    SDL_Rect rect;

    rect.x = pos.GetX() * Game::TILE_SIDE;
    rect.y = pos.GetY() * Game::TILE_SIDE;
    if (forRender) {
        rect.x = (pos.GetX() * Game::TILE_SIDE) - game->getMapOffset();
    }
    if (!superMario) {
        rect.w = texturaMario->getFrameWidth();
        rect.h = texturaMario->getFrameHeight();
    }
    else {
        rect.w = texturaSMario->getFrameWidth();
        rect.h = texturaSMario->getFrameHeight();
    }
    return rect;
}


void Player::resetPos() { //REINICIAR LA POSICION DEL JUGADOR
    pos = posInicio;
}

void Player::changeMario() { superMario = !superMario; }

void Player::decreaseLife() {
    if (life > 0) {
        life--;
        if (life == 0) {
            game->endGame(); //cuando no queda vidas acaba el juego
        }
        else {
            game->resetLevel(); // Reinicia el nivel si a¨²n quedan vidas
        }
    }
}
void Player::jump() {
    if (isJumping && altura < MAX_ALTURA) { //cuando se ha pulsado space
        altura++;
        isGrounded = false;
    }
    else if (!isGrounded) { //si ha llegado a la altura maxima y no esta en el suelo
        dir.SetY(1);
    }
}
void Player::render(SDL_Renderer* renderer) {
	
    SDL_Rect rect = getRect(true);

    animateMario();
    
	// Se renderiza.
    renderMarioAnimation(rect, renderer);   

    if (Game::DEBUG){
        Point2D<float> nextPos = pos + dir * MOVE_SPEED;
        SDL_Rect rect2 = createRect(
            nextPos.GetX() * Game::TILE_SIDE - game->getMapOffset(),
            nextPos.GetY() * Game::TILE_SIDE);

        SDL_SetRenderDrawColor(renderer,255,0,0,128 );
        SDL_RenderDrawRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
    }
}

void Player::animateMario() {
    if (dir == DIR_INI) { //cuando se queda quieto
        anim = 0;
    }
    else if (!isGrounded) {//salto
        anim = 6;
    }
    else if (dir.GetX() != 0 && isGrounded)
    {
        if (anim == 0) anim = 2;
        else if (anim == 2) anim = 3;
        else if (anim == 3) anim = 4;
        else if (anim == 4) anim = 0;
        else if (anim == 6) anim = 0;
    }
    else anim = 0;
}

void Player::renderMarioAnimation(const SDL_Rect& rect, SDL_Renderer* renderer) const  {
    if (!superMario) {
        texturaMario->renderFrame(rect, 0, anim, dir.GetX() < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
    else {
        texturaSMario->renderFrame(rect, 0, anim, dir.GetX() < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
}

// Input de teclado cambian la dir del jugador.
void Player::handleEvent(SDL_Event evento) {
    // Escanea la tecla.
    SDL_Scancode tecla = evento.key.keysym.scancode;

    // Al pulsar la tecla...
    if (evento.type == SDL_KEYDOWN) {
        if ((tecla == SDL_SCANCODE_W || tecla == SDL_SCANCODE_SPACE || tecla == SDL_SCANCODE_UP) && isGrounded && !isJumping) {
            dir.SetY(-1);
            isJumping = true;
            altura = 0;
        }
        else if (tecla == SDL_SCANCODE_A || tecla == SDL_SCANCODE_LEFT) {
            dir.SetX(-1);
        }
        else if (tecla == SDL_SCANCODE_S || tecla == SDL_SCANCODE_DOWN) {
            // Mario nunca va abajo, pero se pone la animacion de agacharse.
        }
        else if (tecla == SDL_SCANCODE_D || tecla == SDL_SCANCODE_RIGHT) {
            dir.SetX(1);
        }
    }
    // Al despulsar la tecla...
    else if (evento.type == SDL_KEYUP) {
        if (tecla == SDL_SCANCODE_A || tecla == SDL_SCANCODE_LEFT || tecla == SDL_SCANCODE_D || tecla == SDL_SCANCODE_RIGHT) {
            dir.SetX(0); 
        }
        else if (tecla == SDL_SCANCODE_W || tecla == SDL_SCANCODE_SPACE || tecla == SDL_SCANCODE_UP) {
            isJumping = false;
        }
        
    }
}

void Player::update() {

    Point2D<float> nextPos = pos + dir * MOVE_SPEED;

    if (nextPos.GetX() * Game::TILE_SIDE >= game->getMapOffset()) { //si mario no pasa del borde izq
        SDL_Rect nextCollider = createRect(nextPos.GetX() * Game::TILE_SIDE - game->getMapOffset(), nextPos.GetY() * Game::TILE_SIDE);
        Collision::collision result = game->checkCollision(nextCollider, true);

        if (result.damages) {
            decreaseLife();
        }
        else {
            if (!result.collides) {
                pos = nextPos;
                isGrounded = false;
            }
            else if (result.fromMushroom) {
                if(!superMario) changeMario();
            }
            else if (result.fromEnemy) {
                if (superMario) changeMario();
                else decreaseLife();
            }
            else {
                // Si hay colisión, verificar el margen en función de la dirección
                if (result.intersectRect.h <= margenColi && result.intersectRect.y > nextCollider.y) {
                    // Si hay suficiente margen en la dirección Y, actualiza la posición
                    pos = nextPos;
                    isGrounded = true;
                }
                else {
                    // Detener movimiento si hay colisión y no se puede mover
                    dir = DIR_INI;
                }
            }
            jump();
        }

    }

   
}

Collision::collision Player::hit(const SDL_Rect otherRect) {
    Collision::collision resultadoFinal;
    resultadoFinal.fromPlayer = true;
    resultadoFinal.collides = true;

   return resultadoFinal;
}