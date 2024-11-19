#pragma once

#include "SceneObject.h"


class Pickable : SceneObject
{
protected: 
	Pickable(Game*, std::istream&);
	virtual void triggerAction() = 0;
	Collision hit(SDL_Rect&, bool) override;
};

