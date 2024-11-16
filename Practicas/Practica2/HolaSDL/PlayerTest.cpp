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
        w = h = 0; // luego modificar esto

        posInicio = pos;
    }
    catch (...) {
        std::cout << "Error creando Player.";
    }
}

SDL_Rect Player::createRect(float x, float y) {
    // Se crea el rect.
    SDL_Rect rect;

    if (!superMario) { // MARIO.
        rect.w = texturaMario->getFrameWidth() - 8;
        rect.h = texturaMario->getFrameHeight();
    }
    else { // SUPER MARIO.
        rect.w = texturaSMario->getFrameWidth() * 2;
        rect.h = texturaSMario->getFrameHeight() * 2;
    }
    rect.x = x;
    rect.y = y;

    return rect;
}

SDL_Rect Player::getRect(bool forRender) const {
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
}

void Player::changeMario() { superMario = !superMario; }

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