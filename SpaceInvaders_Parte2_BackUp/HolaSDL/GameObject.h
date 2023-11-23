#pragma once
#include <iostream>
#include <ostream>

class Game;
class GameObject
{
protected:
	Game* game;
public:
	GameObject(Game* game);
	~GameObject();
	virtual void render() const = 0;
	virtual void update() = 0;
	//virtual void save(ostream& os) = 0;

};

