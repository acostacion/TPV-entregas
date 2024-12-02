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
	// Referencias.
	Texture* texture = nullptr;
	Game* game = nullptr;

	// Propiedades.
	Point2D<float>pos;
	float width = 0;
	float height = 0;

	// HAY QUE METER LO DEL ANCHOR.

	SDL_Rect getCollisionRect();
	SDL_Rect getRenderRect() const;

	// Iterador de sceneobjects.
	GameList<SceneObject>::anchor anchor;

public:
	// Constructores y Destructores.
	SceneObject(Game* _game, Point2D<float> _pos, float _W, float _h, Texture* _textue);

	// Métodos.
	virtual Collision hit(const SDL_Rect& rect, Collision::Target target) = 0; // Detecta colisión con otro rectángulo
	Collision tryToMove(const Vector2D<float>& speed, Collision::Target target);

	void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
		this->anchor = std::move(anchor);
	}

	// Getters.
	Point2D<float> getPosition() const { return pos; }
	float getWidth() const { return width; } 
	float getHeight() const { return height; } 
	Texture* getTexture() const { return texture; } 
	
};

