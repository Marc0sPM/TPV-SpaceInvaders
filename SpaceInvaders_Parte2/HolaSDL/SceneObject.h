#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL_rect.h>
#include <list>
class SceneObject : public GameObject
{
protected:
	Point2D<int> pos;
	int lifes, width, height;
	std::list<SceneObject*>::iterator listIterator; // no se que es pero el barbas lo tiene

public:
	SceneObject(Game* _game, Point2D<int> _pos, int _lifes, int _width, int _height);
	virtual void hit(SDL_Rect attackRect, char src);
	void setListIterator(std::list<SceneObject*>::iterator iterator);
};

