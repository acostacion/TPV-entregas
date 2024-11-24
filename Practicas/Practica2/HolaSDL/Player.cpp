#include "checkML.h"
#include "Player.h"
#include "Game.h" // para evitar inclusiones cruzadas.

Player::Player(Game* _game, std::istream& in) 
    : SceneObject(_game, pos, width, height, texture), game(_game)
{
    try {

        in >> pos; // lee pos.
        pos = pos - Point2D<float>(0, 1); // ajusta pos.
        in >> life; // vidas.

        texture = game->getTexture(Game::MARIO); // Inicialmente es Only Mario.
        posInicio = pos;
    }
    catch (...) {
        std::cout << "Error creando Player.";
    }
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect rect = getRect(true);

    // Se renderiza.
    updateAnimation();
    renderAnimation(rect, renderer);

    if (DEBUG) {
        Point2D<float> nextPos = pos + dir * MOVE_SPEED;
        SDL_Rect debugRect = createRect(
            nextPos.GetX() * TILE_SIDE - game->getMapOffset(),
            nextPos.GetY() * TILE_SIDE, width, height);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
        SDL_RenderDrawRect(renderer, &debugRect);
        SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
    }
}

void Player::handleEvent(SDL_Event evento) {
    // Escanea la tecla.
    SDL_Scancode tecla = evento.key.keysym.scancode;

    // Al pulsar la tecla...
    if (evento.type == SDL_KEYDOWN) {
        if ((tecla == SDL_SCANCODE_W || tecla == SDL_SCANCODE_SPACE || tecla == SDL_SCANCODE_UP) && isGrounded && !isJumping) {
            dir.SetY(-1);
            isJumping = true;
        }
        else if (tecla == SDL_SCANCODE_A || tecla == SDL_SCANCODE_LEFT) {
            dir.SetX(-1);
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

void Player::update() 
{
    Point2D<float> nextPosition = pos + dir * MOVE_SPEED;

    // Verificar que Mario no exceda el borde izquierdo del mapa
    if (nextPosition.GetX() * TILE_SIDE < game->getMapOffset() 
        || nextPosition.GetY() * TILE_SIDE + TILE_SIDE * 2 > WIN_HEIGHT){
        game->resetLevel();
        return;
    }

    SDL_Rect nextCollider = createRect(nextPosition.GetX() * TILE_SIDE, 
        nextPosition.GetY() * TILE_SIDE, width, height);
    Collision result = game->checkCollision(nextCollider, true);
    result.horizontal = 2;
    result.vertical = 2;

    // Si hay da�o en la colisi�n, reducir la vida
    if (result.result = Collision::DAMAGE) {
        decreaseLife();
        return;
    }

    // Sin colisi�n: actualizar posici�n y estado de "en el suelo"
    if (result.result = Collision::NONE) {
        pos = nextPosition;
        isGrounded = false;
        jump();
        return;
    }

    // Colisi�n con un hongo: cambiar a Super Mario si no lo es. 
    if (result.result == Collision::EFFECT) {
        setSuperMario(true);
    }
    // Colisi�n con un enemigo: revertir Super Mario o reducir vida
    else if (result.result == Collision::DAMAGE) {
        if (superMario) setSuperMario(false);
        else decreaseLife();
    }
    // Colisi�n con otro obst�culo: verificar el margen de colisi�n
    else if (result.intersectRect.h <= MARGEN_COLI && result.intersectRect.y > nextCollider.y) {
        // Si hay margen suficiente en la direcci�n Y, actualizar posici�n y estado de "en el suelo"
        pos = nextPosition;
        isGrounded = true;
    }
    // Colisi�n sin margen: detener el movimiento
    else {
        dir = DIR_INI;
    }

    // Intenta realizar salto
    jump();
}

Collision Player::hit(const SDL_Rect& otherRect, bool fromPlayer) {
    fromPlayer = false; // FROMPLAYER SIEMPRE SERA FALSE AQU�.

    Collision resultadoFinal;
    resultadoFinal.horizontal = 2;
    resultadoFinal.vertical = 2;
    resultadoFinal.result = 
    resultadoFinal.collides = true;

    return resultadoFinal;
}

#pragma region Subm�todos
SDL_Rect Player::createRect(float x, float y, float w, float h) {
    // Se crea el rect.
    SDL_Rect rect;

    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;

    return rect;
}

void Player::renderAnimation(const SDL_Rect& rect, SDL_Renderer* renderer) {
    texture->renderFrame(rect, 0, anim, dir.GetX() < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Player::jump() {
    if (isJumping && height < MAX_HEIGHT) {
        // Aumentar altura si est� saltando y no ha alcanzado la altura m�xima
        height++;
        isGrounded = false;
    }
    else if (!isGrounded) {
        // Si alcanz� la altura m�xima y a�n no ha tocado el suelo, empieza a caer
        dir.SetY(1);
    }
}

void Player::decreaseLife() {
    if (life > 0) {
        life--;
        if (life == 0) {
            dead = true;
        }
        else {
            game->resetLevel(); // Reinicia el nivel si a��n quedan vidas
        }
    }
}

void Player::updateAnimation() {
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

void Player::setSuperMario(bool isSuperMario) { // HACER AHORA.
    superMario = isSuperMario;
    if (isSuperMario) { // SUPERMARIO.
        texture = game->getTexture(Game::SUPERMARIO);
        width = texture->getFrameWidth() * 2;
        height = texture->getFrameHeight() * 2;
    }
    else { // MARIO ONLY.
        texture = game->getTexture(Game::MARIO);
        width = texture->getFrameWidth() - 8;
        height = texture->getFrameHeight();
    }
}
#pragma endregion