#pragma once
#include "Alien.h"
class ShooterAlien : public Alien
{
protected:
	int remainingTime = 2000;
public:
	bool update();
};

