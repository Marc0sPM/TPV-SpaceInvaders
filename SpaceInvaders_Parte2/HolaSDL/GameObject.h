#pragma once
#include "Game.h"
#include <iostream>

class GameObject
{
protected:
	Game* game;
public:
	GameObject();
	~GameObject();
	virtual void render() = 0;
	virtual bool update() = 0;
	virtual void save(ostream& os) = 0; //rellenar

};

