#pragma once

#include "SceneObject.h"

class Game;
class Pickable : SceneObject
{
protected: 
	Pickable(Game*, std::istream&);
	Pickable(Game*, const Point2D<float>&);
	virtual void triggerAction() = 0;
	
	virtual void render(SDL_Renderer* renderer) const override;
	virtual void update() override;

	Collision hit(const SDL_Rect&, Collision::Target) override;
};

