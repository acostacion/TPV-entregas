#pragma once
#include "CheckML.h"
#include "SceneObject.h"

#include <fstream>
#include <iostream>

class Enemy : public SceneObject
{
protected:

	bool dead;
	bool frozen;

	bool getFrozen()const { return frozen; }

	bool isDead()const { return dead; }
	Collision::collision hit(const SDL_Rect& other, bool fromPlayer) override;

};

