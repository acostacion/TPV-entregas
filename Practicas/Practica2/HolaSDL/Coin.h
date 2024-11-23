#pragma once
#include "Pickable.h"
#include "Game.h"
class Game;
class Coin : public Pickable
{
	void triggerAction(){game->givePoints(200);}
};

