#include "checkML.h"
#include "Player.h"
#include "Game.h" // para evitar inclusiones cruzadas.

Player::Player(Game* _game, std::istream& in) 
    : SceneObject(_game, pos, width, height, _game->getTexture(Game::MARIO)), game(_game), texture(_game->getTexture(Game::MARIO)) // Inicialmente es Only Mario.
{
    try {

        in >> pos; // lee pos.
        pos = pos - Point2D<float>(0, 1); // ajusta pos.
        in >> life; // vidas.
        posInicio = pos;

        width = texture->getFrameWidth();
        height = texture->getFrameHeight();
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
    if (nextPosition.GetX() * TILE_SIDE < game->getMapOffset() || 
        nextPosition.GetY() * TILE_SIDE + TILE_SIDE * 2 > WIN_HEIGHT){
        game->resetLevel();
        return;
    }

    // Rectángulo que se muee hacia adelante.
    SDL_Rect nextCollider = createRect(nextPosition.GetX() * TILE_SIDE, 
                                       nextPosition.GetY() * TILE_SIDE, 
                                       width, height);

    Collision result = game->checkCollision(nextCollider, Collision::BOTH);

    // Si hay daño en la colisión, reducir la vida
    if (result.result = Collision::DAMAGE) {
        if (superMario) { // Si te hacen daño siendo SMB -> MB.
            setSuperMario(false);
        }
        else { // Si te hacen daño siendo MB -> -vida.
            decreaseLife();
        }
        return;
    }

    // Colisión con un hongo: cambiar a Super Mario si no lo es. 
    if (result.result == Collision::EFFECT) {
        setSuperMario(true);
    }

    if (result.result = Collision::NONE) { // Sin colisión: actualizar posición y estado de "en el suelo"
        pos = nextPosition;
        isGrounded = false;
        jump();
        return;
    }
    else if (result.vertical == 1) { // Colisión con otro obstáculo: verificar el margen de colisión
        
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

Collision Player::hit(const SDL_Rect& otherRect, Collision::Target target) {
    Collision resultadoFinal;

    //resultadoFinal.horizontal = 2;
   // resultadoFinal.vertical = 2;
   // resultadoFinal.result = Collision::DAMAGE

    return resultadoFinal;
}

#pragma region Submétodos
SDL_Rect Player::getRect(bool forRender)const {
    SDL_Rect rect;

    rect.x = pos.GetX() * TILE_SIDE;
    rect.y = pos.GetY() * TILE_SIDE;
    if (forRender) {
        rect.x = (pos.GetX() * TILE_SIDE) - game->getMapOffset();
    }

    rect.w = texture->getFrameWidth();
    rect.h = texture->getFrameHeight();

    return rect;
}

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
        // Aumentar altura si está saltando y no ha alcanzado la altura máxima
        height++;
        isGrounded = false;
    }
    else if (!isGrounded) {
        // Si alcanzó la altura máxima y aún no ha tocado el suelo, empieza a caer
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
            game->resetLevel(); // Reinicia el nivel si a¨²n quedan vidas
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