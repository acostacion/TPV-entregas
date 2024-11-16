#include "PlayerTest.h"

PlayerTest::PlayerTest(Game* _game, std::istream& in) : SceneObject(_game, dir, w, h) // game, pos, w, h.
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