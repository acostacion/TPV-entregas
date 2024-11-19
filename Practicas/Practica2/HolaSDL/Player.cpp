#include "Player.h"
#include <algorithm>

void Player::render(SDL_Renderer* renderer) {

    
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
            height = 0;
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
    // Calcular la próxima posición
    Point2D<float> nextPosition = pos + dir * MOVE_SPEED;
    // Verificar que Mario no exceda el borde izquierdo del mapa
    if (nextPosition.GetX() * Game::TILE_SIDE < game->getMapOffset()) return;
    if (nextPosition.GetY() * Game::TILE_SIDE + Game::TILE_SIDE * 2 > Game::WIN_HEIGHT) {
        game->resetLevel();
        return;
    }

    SDL_Rect nextCollider = createRect(nextPosition.GetX() * Game::TILE_SIDE, nextPosition.GetY() * Game::TILE_SIDE);
    Collision::collision result = game->checkCollision(nextCollider, true);


    // Si hay daño en la colisión, reducir la vida
    if (result.damages) {
        decreaseLife();
        return;
    }

    // Sin colisión: actualizar posición y estado de "en el suelo"
    if (!result.collides) {
        pos = nextPosition;
        isGrounded = false;
        jump();
        return;
    }

    // Colisión con un hongo: cambiar a Super Mario si no lo es
    if (result.fromMushroom) {
        if (!superMario) changeMario();
    }
    // Colisión con un enemigo: revertir Super Mario o reducir vida
    else if (result.fromEnemy) {
        if (superMario) changeMario();
        else decreaseLife();
    }
    // Colisión con otro obstáculo: verificar el margen de colisión
    else if (result.intersectRect.h <= margenColi && result.intersectRect.y > nextCollider.y) {
        // Si hay margen suficiente en la dirección Y, actualizar posición y estado de "en el suelo"
        pos = nextPosition;
        isGrounded = true;
    }
    // Colisión sin margen: detener el movimiento
    else {
        dir = DIR_INI;
    }

    // Intenta realizar salto
    jump();
}



Collision::collision Player::hit(const SDL_Rect otherRect) {
    Collision::collision resultadoFinal;
    resultadoFinal.fromPlayer = true;
    resultadoFinal.collides = true;

    return resultadoFinal;
}