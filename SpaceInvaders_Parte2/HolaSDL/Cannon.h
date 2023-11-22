#pragma once

#include "Vector2D.h"
#include "texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "SceneObject.h"
#include "checkML.h"

const int SPEED = 2;
const Uint32 SHOOT_INTERVAL = 700; //tiempo entre cada disparo (0.8s)
class Game;
class Cannon : public SceneObject
{
protected:
	Texture* textura;
	int remainingTime;
	Vector2D<int> moveDirection;
	bool isMoving;
	Uint32 shootCounter;
	bool canShoot;
	SDL_Rect* rect;
	
	
public:
	Cannon(Point2D<int>& _pos,int _lives,int _remainingTime,Game* _game, Texture* _textura);
	void render() const ;
	bool update();
	void hit();
	void handleEvents(const SDL_Event &event);
	SDL_Rect* getRect() { return rect; }

};

