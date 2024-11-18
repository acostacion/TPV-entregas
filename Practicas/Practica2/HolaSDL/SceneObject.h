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
	Point2D<float> pos;
	Point2D<float> nextPosition;
	Point2D<float> dir;
	Texture* textura;
	int anim;
	int timer;
	int width, height;
	bool isGrounded;

	const int MARGIN_Y = 5;
	const int MARGIN_X = 5;

	const float MOVE_SPEED = 0.3f; // velocidad de movimiento.
	GameList<SceneObject>::anchor listAnchor;
public:
	// Métodos.
	SceneObject(Game*, Point2D<float>&, Point2D<float>&, Game::TextureName);
	
	SceneObject(Game*, std::istream&);


	void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
		listAnchor = std::move(anchor);
	}

	void removeFromList() {
		listAnchor.unlink();
	}



	void update() override;


	virtual Collision::collision hit(const SDL_Rect& other, bool fromPlayer) = 0;
	
	void tryToMove(Vector2D<int> velocity, bool allowVertical);
	
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