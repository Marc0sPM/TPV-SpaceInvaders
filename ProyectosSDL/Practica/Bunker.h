#pragma once
#include "Vector2D.h"
#include "texture.h"
using namespace std;
class Bunker
{
private:
	Point2D<int> pos;
	int lifes;
	Texture* textura;

public:
	Bunker();
	Bunker(Point2D<int> _pos, int _lifes, Texture _textura);

	void render() const;
	void update();
	void hit();
};

