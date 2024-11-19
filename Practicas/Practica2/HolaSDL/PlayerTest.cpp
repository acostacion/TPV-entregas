#include "PlayerTest.h"

PlayerTest::PlayerTest(Game* _game, std::istream& in) : SceneObject(_game, pos, w, h) // game, pos, w, h.
{
    try {
        in >> pos; // lee pos.
        pos = pos - Point2D<float>(0, 1); // ajusta pos.
        in >> life; // vidas.

        texturaMario = game->getTexture(Game::MARIO);
        texturaSMario = game->getTexture(Game::SUPERMARIO);
        verticalVelocity = 0;

        superMario = false;
        isGrounded = false;
        isJumping = false;
        dir = DIR_INI;
        dead = false;

        if (!superMario) { // MARIO.
            w = texturaMario->getFrameWidth() - 8;
            h = texturaMario->getFrameHeight();
        }
        else { // SUPER MARIO.
            w = texturaSMario->getFrameWidth() * 2;
            h = texturaSMario->getFrameHeight() * 2;
        }

        posInicio = pos;
    }
    catch (...) {
        std::cout << "Error creando Player.";
    }
}

SDL_Rect PlayerTest::createRect(float x, float y, float w, float h) {
    // Se crea el rect.
    SDL_Rect rect;

    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;

    return rect;
}

/*SDL_Rect Player::getRect(bool forRender) const {
    SDL_Rect rect;

    rect.x = pos.GetX() * Game::TILE_SIDE;
    rect.y = pos.GetY() * Game::TILE_SIDE;

    if (!superMario) {
        rect.w = texturaMario->getFrameWidth();
        rect.h = texturaMario->getFrameHeight();
    }
    else {
        rect.w = texturaSMario->getFrameWidth() * 2;
        rect.h = texturaSMario->getFrameHeight() * 2;
        rect.y = pos.GetY() * Game::TILE_SIDE;
    }
    if (forRender) {
        rect.x = (pos.GetX() * Game::TILE_SIDE) - game->getMapOffset();
        rect.y -= 3;

    }
    return rect;
}*/

void PlayerTest::changeMario() { superMario = !superMario; }
void PlayerTest::resetPos() { pos = posInicio; }

void PlayerTest::decreaseLife() {
    if (life > 0) {
        life--;
        if (life == 0) dead = true;
        else {
            game->resetLevel(); // Reinicia el nivel si a¨²n quedan vidas
        }
    }
}

void PlayerTest::jump() {
    if (isJumping && height < MAX_HEIGHT) {
        // Aumentar altura si está saltando y no ha alcanzado la altura máxima
        height++;
        isGrounded = false;
    }
    else if (!isGrounded) {
        // Si alcanzó la altura máxima y aún no ha tocado el suelo, empieza a caer
        dir.SetY(1);
    }
}

void PlayerTest::render(SDL_Renderer* renderer) {
    SDL_Rect rect = getRect(true);

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

    // Se renderiza.
    renderMarioAnimation(rect, renderer);

    if (Game::DEBUG) {
        Point2D<float> nextPos = pos + dir * MOVE_SPEED;
        SDL_Rect rect2 = createRect(
            nextPos.GetX() * Game::TILE_SIDE - game->getMapOffset(),
            nextPos.GetY() * Game::TILE_SIDE);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
        SDL_RenderDrawRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
    }
}

void PlayerTest::renderMarioAnimation(const SDL_Rect& rect, SDL_Renderer* renderer) const {
    if (!superMario) {
        texturaMario->renderFrame(rect, 0, anim, dir.GetX() < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
    else {
        texturaSMario->renderFrame(rect, 0, anim, dir.GetX() < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
}

// Input de teclado cambian la dir del jugador.
void PlayerTest::handleEvent(SDL_Event evento) {
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

void PlayerTest::update() {
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