#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "checkML.h"
using namespace std;
class Bunker
{
private:
	Point2D<int> pos;
	int lifes;
	Texture* textura;
	int currentFrame;
	int maxLife;
	int lifePercentage;
	SDL_Rect* rect;

public:
	Bunker();
	Bunker(Point2D<int>& _pos, int _lifes, Texture* _textura);
	void render() ;
	bool update();
	void hit();
	SDL_Rect* getRect() const { return rect; }
};

