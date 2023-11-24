#pragma once
#include "GameObject.h"
#include "checkML.h"
#include "Vector2D.h"


class Game;

class Mothership : public GameObject
{
protected:
	int alienCont;
	
public: 
	Mothership(Game* _game);
	void update()override;
	void render() const override;
	void addAlien();
};

