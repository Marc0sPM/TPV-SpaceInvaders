#pragma once
#include "SDL.h"
#include <list>
#include "SceneObject.h"
#include "gameList.h"
#include "Cannon.h"

class PlayState
{
private:
	GameList<SceneObject> sceneObjects;
	Cannon* cannon;
public:
	virtual void update();
	virtual void render() const;
	bool damage(SDL_Rect* laserRect, char& src);
	virtual void hasDied(std::list<SceneObject*>::iterator& iterator);
	int getRandomRange(int min, int max);

};

