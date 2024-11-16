#pragma once
#include "CheckML.h"
#include "SceneObject.h"

#include <fstream>
#include <iostream>

class PlayerTest : public SceneObject
{
private:
	Game* game;
	Point2D<float> dir;
	Point2D<float> pos;
	Point2D<float> posInicio;// para el reinicio
	bool isGrounded; // si esta en el suelo
	bool isJumping;
	bool superMario = false;
	bool dead;
	Texture* texturaMario; //mario
	Texture* texturaSMario; // superMario
	int life;
	float verticalVelocity;

public:

	PlayerTest(Game*, std::istream&); // constructora

};

