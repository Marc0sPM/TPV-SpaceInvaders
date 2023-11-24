#pragma once
#include "GameObject.h"
class Game;
class Mothership : public GameObject
{
protected:
	int cant;
public: 
	Mothership(Game* _game, int _cant);
	void update()override;
	void render() const override;
};

