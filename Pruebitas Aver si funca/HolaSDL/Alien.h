#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "Mothership.h"

const int ALIEN_SPEED = 10; //Pixeles de movimiento
class Game;
//class Mothership;
class Alien : public SceneObject
{
private:
	SDL_Rect* rect;
	
protected:
	Mothership* motherShip;
	Texture* textura;
	int subtipo;
	
public:

	Alien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo, Mothership* _motherShip);
	Point2D<int> getPos() const;
	void render() const override;
	void update() override;
	bool hit(SDL_Rect* attackRect, char src);
	SDL_Rect getRect() const { return *rect; }
};

