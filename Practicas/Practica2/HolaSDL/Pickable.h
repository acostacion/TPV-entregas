#pragma once
#include "SceneObject.h"

class Pickable : public SceneObject
{
protected:
	Collision hit(const SDL_Rect& region, Collision::Target target);
};

