#pragma once

#include "SceneObject.h"


class Pickable : SceneObject
{
protected: 
	Pickable(Game*, std::istream&);
	virtual void triggerAction() = 0;
	
	
	virtual void render(SDL_Renderer* renderer) const override;
	virtual void update() override;

	virtual Collision hit(const SDL_Rect&, bool) override;
};

