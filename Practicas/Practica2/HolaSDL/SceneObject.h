#pragma once
#include "GameObject.h"
#include "gameList.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>
#include <iostream>
#include <fstream>

class Game;
class SceneObject : public GameObject{ // SceneObject hereda de GameObject.
protected:
	// Atributos.
#pragma region Movement
	Point2D<float> pos;
	Point2D<float> nextPosition;
	Point2D<float> dir;
	float moveSpeed = 0.3f; // velocidad de movimiento.

	bool isGrounded; // si esta en el suelo

	const int MARGIN_Y = 5;
	const int MARGIN_X = 5;

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
	SceneObject(Game*, Point2D<float>&, Point2D<float>&);
	
	SceneObject(Game*, std::istream&);


	void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
		listAnchor = std::move(anchor);
	}

	void removeFromList() {
		listAnchor.unlink();
	}



	void update() override;


	virtual Collision::collision hit(const SDL_Rect& other, bool fromPlayer) = 0;
	
	Collision tryToMove(const Vector2D<int>& speed, Collision::Target attack);
	
	virtual ~SceneObject() = default;

	SDL_Rect createRect(int, int);

	float getX()const { return this->pos.GetX(); }

	Point2D<float> getPos();
	Point2D<float> getDir();
};

inline Point2D<float>
SceneObject::getPos() {
	return pos;
}

inline Point2D<float>
SceneObject::getDir() {
	return dir;
}