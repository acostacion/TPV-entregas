#include "Player.h"
#include <algorithm>

Player::Player(Game* game, std::istream& in) 
    : game(game), superMario(false), altura(0), isGrounded(false), isJumping(false), dir(DIR_INI)
{
	in >> pos; // lee pos.
	pos = pos - Point2D<float>(0, 1.5); // coloca a pos.
	in >> life; // el n�mero de vidas

	texturaMario = game->getTexture(Game::MARIO);
	texturaSMario = game->getTexture(Game::SUPERMARIO);

    invulnerable = false;
    verticalVelocity = 0;


    posInicio = pos;
}


SDL_Rect Player::createRect(float x, float y) {
    // Se crea el rect.
    SDL_Rect rect;

    // Se le da dimensiones y posición.
    if (!superMario) {
        rect.w = texturaMario->getFrameWidth();
        rect.h = texturaMario->getFrameHeight();
    }
    else {
        rect.w = texturaSMario->getFrameWidth();
        rect.h = texturaSMario->getFrameHeight();
    }
    rect.x = x +8;
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

void Player::changeMario() {
    if (superMario) {
        superMario = false;
    }
    else {
        superMario = true;;
    }
}

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

    // Frame de la animacion

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
      
    } else anim = 0;

    
	// Se renderiza.
    if (!superMario) {
        texturaMario->renderFrame(rect, 0, anim, dir.GetX() < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
    else {
        texturaSMario->renderFrame(rect, 0, anim, dir.GetX() < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

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
            else if (result.fromMushroom && !superMario) {
                superMario = true;
                changeMario();
            }
            else if (result.fromEnemy && superMario) {
                superMario = false;
                changeMario();
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

    /*
    ////collider.y = pos.GetY() + dir.GetY();
   
    //Collision::collision collisionRes2 = game->checkCollision(collider, true);

    //if (collisionRes2) {
    //    if (verticalVelocity > 0) {
    //        // Colisión desde abajo, estamos cayendo hacia el suelo
    //        collider.y = collisionRes2.intersectRect.y - collider.h;
    //        isGrounded = true;
    //        verticalVelocity = 0; // Detener el movimiento vertical
    //    }
    //    else if (verticalVelocity < 0) {
    //        // Colisión desde arriba (ej., saltar contra el techo)
    //        collider.y = collisionRes2.intersectRect.y + collisionRes2.intersectRect.h;
    //        verticalVelocity = 0; // Detener el movimiento hacia arriba
    //    }
    //    pos = Point2D<float>(collider.x, collider.y);

    //}else {
    // // Si no hay colisión, sigue en el aire
    //    isGrounded = false;
    //}

    //if (dir.GetX() > 0) {
    //    collider.x = pos.GetX() + dir.GetX();


    //    // Comprobar colisiones horizontales con el mapa
    //    collisionRes2 = game->checkCollision(collider, true);

    //    if (collisionRes2.collides) {
    //        // Colisión a la derecha (pared u obstáculo)
    //        collider.x = collisionRes2.intersectRect.x - collider.w;
    //    }
    //    else {
    //        collider.x += MOVE_SPEED;

    //    }
    //    pos = Point2D<float>(collider.x, collider.y);

    //}
    //else if (dir.GetX() <  0) {
    //    collider.x = pos.GetX() + dir.GetX();

    //    // Comprobar colisiones horizontales con el mapa
    //    collisionRes2 = game->checkCollision(collider, true);

    //    if (collisionRes2.collides) {
    //        // Colisión a la izquierda (pared u obstáculo)
    //        collider.x = collisionRes2.intersectRect.x + collisionRes2.intersectRect.w;
    //    }
    //    else {
    //        collider.x -= MOVE_SPEED;

    //    }
    //    pos = Point2D<float>(collider.x, collider.y);

    //}


    //collider.x = pos.GetX();
    //collider.y = pos.GetY();*/

    //if (!isGrounded) {
    //    dir.SetY(dir.GetY() + GRAVITY); // GRAVITY es un valor positivo que representa la gravedad
    //}

    // Colisión y movimiento en el eje Y.
    //if (!isGrounded) {
    
    //collider.y = pos.GetY() + dir.GetY();
    //auto colY = game->checkCollision(collider, false); // Comprueba si colisiona.

    //if (colY.collides) {
    //    if (dir.GetY() > 0 ) { // baja
    //        // Cuando cae.
    //        isGrounded = true;
    //        collider.y += colY.intersectRect.y - collider.h/32;
    //        dir.SetY(0);
    //        std::cout << "Collides" << "\n";
    //        std::cout << "Pos X: " << pos.GetX() << ", Pos Y: " << pos.GetY() << std::endl;
    //        std::cout << "Dir X: " << dir.GetX() << ", Dir Y: " << dir.GetY() << std::endl;
    //        std::cout << "Collider X: " << collider.x << ", Collider Y: " << collider.y << std::endl;
    //    }
    //    else {

    //    }
    //}
   
    ////}
    //
    //
    //// Colisión y movimiento en el eje X.
    //if (moving) {
    //    pos.SetX(pos.GetX() + dir.GetX()); // posX = posX + dirX
    //    collider.x = pos.GetX();

    //    // Comprueba si colisiona.
    //    auto colX = game->checkCollision(collider, true);
    //    if (colX.collides) {
    //        dir.SetX(0);
    //    }
    //}
    //else {
    //    // DECELERATION cuando deja de moverse.
    //    dir.SetX(dir.GetX() * (1.0f - DECELERATION));
    //    if (std::abs(dir.GetX()) < 0.1f) dir.SetX(0);
    //}
    //if (dir.GetX() > 0) movingDer = true;

    //if (pos.GetX() < 0) { // no se vaya por la izquierda
    //    pos.SetX(0);
    //}
    //else if (pos.GetX() > Game::WIN_TILE_WIDTH / 2) // no pase de la mitad
    //{
    //    pos.SetX(game->WIN_TILE_WIDTH / 2);
    //}
    //pos.SetX(pos.GetX() + dir.GetX());
    //pos.SetY(pos.GetY() + dir.GetY());
    //if (pos.GetX() < 0) { // no se vaya por la izquierda
    //    pos.SetX(0);
    //}
    //else if (pos.GetX() > Game::WIN_TILE_WIDTH / 2) // no pase de la mitad
    //{
    //    pos.SetX(game->WIN_TILE_WIDTH / 2);
    //}
    //collider.x = pos.GetX();
    //collider.y = pos.GetY();
   
    //
    //
   



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
    Collision::collision resultadoFinal;
    //SDL_Rect result = createRect(0, 0, 0, 0);
   
    //SDL_IntersectRect(&collisionRes.intersectRect, &collider, &result);
    //SDL_bool haColisionado= SDL_HasIntersection(&collisionRes.intersectRect, &collider);
    //if (haColisionado) {

    //}

    //if (!invulnerable) {
    //    if (superMario) { superMario = false; invulnerable = true; invulnerableTimer = SDL_GetTicks(); }

    //    else {
    //        life--; if (life <= 0) { // Fin del juego 
    //        } 
    //    } 
    //} else if (SDL_GetTicks() - invulnerableTimer > 2000) { invulnerable = false; }
    //        
    return resultadoFinal;
}