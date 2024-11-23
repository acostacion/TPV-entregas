#pragma once	
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
	float width = texture->getFrameWidth();
	float height = texture->getFrameHeight();

	// Referencias.
	Texture* texture = nullptr;
	Game* game = nullptr;

	// HAY QUE METER LO DEL ANCHOR.

	SDL_Rect getCollisionRect();
	SDL_Rect getRenderRect() const;

public:
	// Constructores y Destructores.
	SceneObject(Game* _game, Point2D<float>& _pos, float& _W, float& _h, Texture* _textue);

	// Métodos.
	virtual Collision hit(const SDL_Rect& otherRect, bool fromPlayer) = 0; // Detecta colisión con otro rectángulo
	Collision tryToMove(const Vector2D<float>& speed, Collision::Target target);

	// Getters.
	Point2D<float> getPosition() const { return pos; }
	float getWidth() const { return width; } 
	float getHeight() const { return height; } 
	Texture* getTexture() const { return texture; } 
	
};

