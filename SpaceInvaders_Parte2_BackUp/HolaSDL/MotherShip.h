#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"
class Game;
class MotherShip : public GameObject
{
protected:
	Vector2D<int> aliensDirection = { 1, 0 };
	bool canMove = true; //temporal
public:
	MotherShip(Game* _game);
	~MotherShip();

	Vector2D<int> getDirection() const { return aliensDirection; }
	bool shouldMove();

	bool cannotMove(); //no se si es bool
	bool alienDied();

	bool haveLanded();
	int getAlienCount() const;


};

