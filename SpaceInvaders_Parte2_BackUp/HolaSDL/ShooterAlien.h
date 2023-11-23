#pragma once
#include "Alien.h"
#include "Game.h"
#include "MotherShip.h"

class ShooterAlien : public Alien
{
protected:
	int reloadTime;
public:
	ShooterAlien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo, int _reloadTime, MotherShip* _motherShip);
	bool update(Uint32 deltaTime);
};

