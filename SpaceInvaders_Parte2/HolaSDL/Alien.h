#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "checkML.h"
#include "SceneObject.h"
#include "MotherShip.h"

int ALIEN_SPEED = 10; //Pixeles de movimiento
const Uint32 MOVE_INTERVAL = 800;
class Game;
class Alien : public SceneObject
{
private:
	int subtipo;
	SDL_Rect* rect;
protected:
	Texture* textura;
	MotherShip* motherShip;
public:

	Alien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo, MotherShip* _motherShip);
	Point2D<int> getPos() const;
	void render() const override;
	void update() override;
	void hit(SDL_Rect attackRect, bool src);
	SDL_Rect getRect() const { return *rect; }
};

