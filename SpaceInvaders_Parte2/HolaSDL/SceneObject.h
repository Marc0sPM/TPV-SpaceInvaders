#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL_rect.h>

class SceneObject : public GameObject
{
protected:
	Point2D<int> pos;
	int lives, width, height;

private:
	SceneObject(Game* _game, Point2D<int> _pos, int _lives, int _width, int _height);
	virtual void hit(SDL_Rect attackRect, bool src);
};

