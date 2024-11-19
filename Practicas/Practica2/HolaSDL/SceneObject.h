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
	float moveSpeed; // velocidad de movimiento.

	bool isGrounded; // si esta en el suelo
	bool dead;

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

	virtual void animation()=0;


	virtual Collision::collision hit(const SDL_Rect& other, bool fromPlayer) = 0;
	
	Collision tryToMove(const Vector2D<int>& speed, Collision::Target attack);
	
	virtual Collision hit(SDL_Rect&, bool) = 0;
	
	virtual ~SceneObject() = default;

	SDL_Rect createRect(int, int)const;

	float getX()const { return this->pos.GetX(); }

	Point2D<float> getPos() const;
	Point2D<float> getDir() const;
	bool isDead()const { return dead; } // Está vivo si life >0.

};

inline Point2D<float>
SceneObject::getPos() const {
	return pos;
}

inline Point2D<float>
SceneObject::getDir()const {
	return dir;
}