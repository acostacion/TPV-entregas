#include "CheckML.h"
#include "Blocks.h"

Blocks::Blocks(Game* _game, std::istream& in) : SceneObject(_game, in)
{
	action = Action::nada;
	tipo = Variant::ladrillo;
	timer = 3;

	char c;
	in >> c;
	switch (c) {
	case 'B': // Si es un bloque ladrillo... 
		tipo = Variant::ladrillo;
		action = Action::nada;
		animFrame = 5;
		break;

	case '?': // Si es un bloque "?"...
		tipo = Variant::sorpresa;
		in >> c;
		anim = true;

		// c true -> action es moneda : c false -> action es potenciador
		action = (c == 'C') ? Action::moneda : Action::potenciador;

		animFrame = 0;
		break;

	case 'H': // Si es un bloque oculto...
		tipo = Variant::oculto;
		action = (c == 'C') ? Action::moneda : Action::potenciador;
		animFrame = 6;
		break;
	}

	textura = _game->getTexture(Game::BLOCKS); // obtiene la textura.
};



Collision
Blocks::hit(const SDL_Rect& region, Collision::Target target)
{
	// Calcula la intersección
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	if (hasIntersection) {
		Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };

		// [...] Manejo del efecto del bloque

		return collision;
	}

	return NO_COLLISION;
}



void Blocks::animation() {

	// si es el sorpresa
	if (timer == 0 && anim) {

		if (animFrame == 0) animFrame = 1;
		else if (animFrame == 1) animFrame = 2;
		else if (animFrame == 2) animFrame = 3;
		else if (animFrame == 3) animFrame = 0;
	}
}

void Blocks::render(SDL_Renderer* renderer) const{

	SDL_Rect rect = createRect(pos.GetX(), pos.GetY());
	textura->renderFrame(rect, 0, animFrame); // Se renderiza.

	if (Game::DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Blocks::changeSprite(){
   	if (tipo == Variant::ladrillo) {
		animFrame = 5;
	}
	else if (tipo == Variant::vacio) {
		animFrame = 4;
	}
	else if (tipo == Variant::oculto) {
		animFrame = 6;
	}
	anim = false; // Si cambian de tipo detiene animacion.
}

void Blocks::update() {
	// Va decrementando el temporizador si esta activo y lo reinicia al llegar 
	if (timer >= 0) {
		timer--;
	}
	else {
		timer = 3;
	}
}

