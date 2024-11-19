#pragma once
#include "GameObject.h"
#include "gameList.h"
#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <fstream>
#include <iostream>
#include <cmath>

class Game;
class SceneObject : public GameObject { // SceneObject hereda de GameObject.
protected:
	// Atributos.
#pragma region Movement

	Point2D<float> pos;
	Point2D<float> nextPosition;
	Point2D<float> dir;
	Point2D<float> speed;

	bool isGrounded; // si esta en el suelo
	bool dead;

	int moveDelay;
	int moveSpeed;


	const int MARGIN_Y = 5;
	const int MARGIN_X = 5;
	const int SPEED_LIMIT = 5;
	const int MOVE_PERIOD = 15;
	
#pragma endregion

#pragma region References

	Texture* textura;
	int width, height;

#pragma endregion

#pragma region Animation

	int anim; // indice del frame de la animacion
	int timer;

#pragma endregion

	GameList<SceneObject>::anchor listAnchor;

public:
	// Métodos.
	SceneObject(Game*, const Point2D<float>&, const Point2D<float>&);
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;
	SceneObject(Game*, std::istream&);

	Collision tryToMove(const Vector2D<float>&, Collision::Target);

	void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
		listAnchor = std::move(anchor);
	}

	void removeFromList() {
		listAnchor.unlink();
	}

	virtual void animation() = 0;

	//Collision tryToMove(const Vector2D<int>& speed, Collision::Target attack);

	virtual Collision hit(const SDL_Rect&, Collision::Target) = 0;

	virtual ~SceneObject() = default;

	SDL_Rect createRect(int, int)const;

	float getX()const { return this->pos.GetX(); }

	Point2D<float> getPos() const;
	Point2D<float> getDir() const;

	bool isDead() const; 
};

inline bool 
SceneObject::isDead() const { 
	return dead; 
} 

inline Point2D<float>
SceneObject::getPos() const {
	return pos;
}

inline Point2D<float>
SceneObject::getDir()const {
	return dir;
}