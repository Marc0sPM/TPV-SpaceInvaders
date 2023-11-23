#pragma once
#include "Alien.h"
#include "Game.h"

class ShooterAlien : public Alien
{
protected:
	int remainingTime = 2000;
public:
	ShooterAlien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo);
	bool update(Uint32 deltaTime);
};

