#pragma once
#include "checkML.h"	
#include "GameObject.h"
#include "gameList.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Texture.h"
#include <SDL_rect.h>

class Game;

class SceneObject : public GameObject{ // SceneObject hereda de GameObject.
protected:
	// Propiedades.
	Point2D<float>pos;
	float width, height;

	// Referencias.
	Texture* texture = nullptr;
	Game* game = nullptr;
	// HAY QUE METER LO DEL ITERADOR.

public:
	// Constructores y Destructores.
	SceneObject() = default;
	SceneObject(Game* _game, Point2D<float>& _pos, float _W, float _h);

	// Métodos.
	virtual void render()const override = 0;
	virtual Collision::collision hit(const SDL_Rect* other, bool fromPlayer) = 0; // Detecta colisión con otro rectángulo
	// HAY QUE METER EL TRYTOMOVE.

	// Getters.
	Point2D<float> getPosition() const { return pos; }
	float getWidth() const { return width; } 
	float getHeight() const { return height; } 
	Texture* getTexture() const { return texture; } 
};

