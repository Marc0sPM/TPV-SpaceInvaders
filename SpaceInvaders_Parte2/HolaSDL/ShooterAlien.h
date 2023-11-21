#pragma once
#include "Alien.h"
class ShooterAlien : public Alien
{
protected:
	int remainingTime;
private:
	bool update();
};

