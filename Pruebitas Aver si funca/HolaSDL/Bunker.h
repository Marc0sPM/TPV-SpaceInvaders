#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "checkML.h"
#include "SceneObject.h"
using namespace std;
class Bunker : public SceneObject
{
protected:

	Texture* textura;
	int currentFrame;
	int maxLife;
	int lifePercentage;
	SDL_Rect* rect;


public:
	Bunker();
	Bunker(Game* _game, Point2D<int>& _pos, int _lifes, Texture* _textura);
	void render() const override;
	void update() override;
	bool hit(SDL_Rect* otherRect, char otherSrc);
	SDL_Rect* getRect() const { return rect; }
};

