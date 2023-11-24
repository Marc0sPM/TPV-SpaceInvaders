#pragma once
#include "Alien.h"
#include "Game.h"
#include "Mothership.h"

class ShooterAlien : public Alien
{
protected:
	int reloadTime;
public:
	ShooterAlien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo, int _reloadTime, Mothership* _motherShip);
	void update();
};

