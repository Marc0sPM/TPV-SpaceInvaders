#pragma once
#include "Alien.h"
#include "Game.h"

class ShooterAlien : public Alien
{
protected:
	int remainingTime = 2000;
public:
	bool update(Uint32 deltaTime);
};

