#pragma once
#include "SDL.h"
#include <list>
#include "SceneObject.h"
class PlayState
{
private:

public:
	virtual void update();
	virtual void render() const;
	bool damage(SDL_Rect* laserRect, char& src);
	void hasDied(std::list<SceneObject*>::iterator& iterator);
	int getRandomRange(int min, int max);

};

