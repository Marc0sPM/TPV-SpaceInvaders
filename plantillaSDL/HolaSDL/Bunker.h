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
	int currentFrame;
	int maxLife;
	int lifePercentage;

public:
	Bunker();
	Bunker(Point2D<int>& _pos, int _lifes, Texture* _textura);
	void render() const;
	bool update();
	void hit();
	Texture* getTexture() const;
	Point2D<int> getPos();
};

