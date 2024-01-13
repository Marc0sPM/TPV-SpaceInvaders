#pragma once
#include "checkML.h"
#include "Alien.h"



class Mothership;
class Game;

class ShooterAlien : public Alien
{
protected:
	int reloadTime;
	int timeCounter = 0;
public:
	ShooterAlien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo, int _reloadTime, Mothership* _motherShip);
	void update() override;
	void save(std::ostream& os)const;
};

