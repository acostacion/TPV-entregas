#include "PlayerTest.h"

PlayerTest::PlayerTest(Game* _game, std::istream& in) : SceneObject(_game, *(new Point2D<float>(0,0)), 0, 0) // game, pos, w, h.
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


        posInicio = pos;
    }
    catch (...) {
        std::cout << "Error creando Player.";
    }
}