#include "Player.h"
#include <algorithm>

Player::Player(Game* game, std::istream& in) 
    : game(game), flip(SDL_FLIP_NONE), renderer(game->getRender()),
    dir(0,0), superMario(false), anim(0), movingDer(false),moving(false),
    isGrounded(false)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1); // coloca a pos.
	in >> life; // el n�mero de vidas

	texturaMario = game->getTexture(Game::MARIO);
	texturaSMario = game->getTexture(Game::SUPERMARIO);

    collider.h = texturaMario->getFrameHeight() * 2;
    collider.w = texturaMario->getFrameWidth() * 2;
    collider.x = pos.GetX();
    collider.y = pos.GetY();

}

SDL_Rect Player::createRect(float w, float h, float x, float y) {
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

    SDL_Rect renderRect = createRect(
        texturaMario->getFrameWidth(), // w.                        
        texturaMario->getFrameHeight(),  // h.                      
        pos.GetX() * Game::TILE_SIDE,  // x.
        pos.GetY() * Game::TILE_SIDE); // y.

    // Frame de la animacion

    if (!isGrounded) {
        anim = 6;
    }
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

    if (Game::DEBUG){
        Point2D<float> nextPos = pos + dir * MOVE_SPEED;
        SDL_Rect rect2 = createRect(
            texturaMario->getFrameWidth(), 
            texturaMario->getFrameHeight(), 
            nextPos.GetX() * Game::TILE_SIDE, 
            nextPos.GetY() * Game::TILE_SIDE);

        SDL_SetRenderDrawColor(renderer,255,0,0,128 );
        SDL_RenderDrawRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
    }
}

// Input de teclado cambian la dir del jugador.
void Player::handleEvent(SDL_Event evento) {
    dir = Point2D<float>(dir.GetX(), GRAVITY);
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

    // Colisión y movimiento en el eje X.
    if (moving) {
        pos.SetX(pos.GetX() + dir.GetX());
        collider.x = pos.GetX();

        // Comprueba si colisiona.
        auto colX = game->checkCollision(collider, true);
        if (colX.collides) {
            dir.SetX(0);
        }
    }
    else {
        // DECELERATION cuando deja de moverse.
        dir.SetX(dir.GetX() * (1.0f - DECELERATION));
        if (std::abs(dir.GetX()) < 0.01f) dir.SetX(0);
    }

    // Colisión y movimiento en el eje Y.
    if (!isGrounded) {
        dir.SetY(std::min(dir.GetY() + GRAVITY, MAX_FALL_SPEED));
        pos.SetY(pos.GetY() + dir.GetY());
        collider.y = pos.GetY();  

        // Comprueba si colisiona.
        auto colY = game->checkCollision(collider, false);
        if (colY.collides) {
            if (dir.GetY() > 0) {
                // Cuando cae.
                isGrounded = true;
                dir.SetY(0);
                pos.SetY(GROUND_LEVEL);
            }
            else {
                dir.SetY(0);
            }
        }
        else {
            isGrounded = false;
        }
    }

    
    
    
   



    //collider.x = pos.GetX() + dir.GetX();
    //collider.y = pos.GetY() + dir.GetY();

    //collisionRes = game->checkCollision(collider, true); // con el suelo

    //if (!collisionRes) {
    //    pos = Point2D<float>(collider.x, collider.y);
    //    isGrounded = false;
    //    dir = Point2D<float>(dir.GetX(), dir.GetY() + GRAVITY);
    //    std::cout << "No he colisionado con el suelo" << "\n";

    //}
    //else {
    //    if (collisionRes.intersectRect.h > margenColi){
    //        //dir = Point2D<float>(dir.GetX(), MAX_FALL_SPEED);
    //        pos = Point2D<float>(collider.x, pos.GetY());
    //        isGrounded = true;
    //        std::cout << "He colisionado con el suelo" << "\n";

    //    }
    //    else {
    //        pos = Point2D<float>(collider.x, collider.y);
    //        std::cout << "He colisionado con el suelo pero me caigo" << "\n";

    //    }

    //}
    


    //collider.x = pos.GetX() + dir.GetX();
    //

    //collisionRes = game->checkCollision(collider, true); // hacia los lados

    //if (collisionRes) {
    //    if (collisionRes.intersectRect.w > margenColi) {
    //        std::cout << "No puedo moverme" << "\n";
    //        pos = Point2D<float>(pos.GetX(), pos.GetY());
    //        moving = false;
    //    }
    //    else {
    //        std::cout << "Me muevo "<< collider.x << "\n";

    //        pos = Point2D<float>(collider.x, collider.y);
    //    }
    //}
    //else {
    //}
    //pos = pos + dir;


    /*
    
     if (!moving) {
        if (std::abs(dir.GetX()) < DECELERATION) {
            dir = Point2D<float>(0, dir.GetY());
        }
        else {
            dir = Point2D<float>(dir.GetX() * 0.8, dir.GetY());
        }
    }

    */
   
}

Collision::collision Player::hit(const SDL_Rect otherRect) {
    Collision::collision resultadoFinal ;
    SDL_Rect result = createRect(0, 0, 0, 0);
   
    SDL_IntersectRect(&collisionRes.intersectRect, &collider, &result);
    SDL_bool haColisionado= SDL_HasIntersection(&collisionRes.intersectRect, &collider);
    if (haColisionado) {

    }


    return resultadoFinal;
}