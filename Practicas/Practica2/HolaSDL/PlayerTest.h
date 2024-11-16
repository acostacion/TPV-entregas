#pragma once
#include "CheckML.h"
#include "SceneObject.h"

#include <fstream>
#include <iostream>

class PlayerTest : public SceneObject
{
private:
	// REFERENCES.
	Game* game;
	Texture* texturaMario; //mario
	Texture* texturaSMario; // superMario

	// PARAMETERS.
	Point2D<float> dir;
	Point2D<float> pos;
	Point2D<float> posInicio;// para el reinicio
	bool isGrounded; // si esta en el suelo
	bool isJumping;
	bool superMario = false;
	bool dead;
	int life;
	float verticalVelocity;
	float w, h; // width, height.

public:

	PlayerTest(Game*, std::istream&); // constructora

private:
	SDL_Rect createRect(float, float);
	SDL_Rect getRect(bool forRender) const;
	void resetPos(){ pos = posInicio; } // reinicia pos del player.

};

