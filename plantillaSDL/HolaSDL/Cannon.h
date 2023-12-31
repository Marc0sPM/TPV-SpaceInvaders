#pragma once

#include "Vector2D.h"
#include "texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "checkML.h"

const int SPEED = 2;
const Uint32 SHOOT_INTERVAL = 700; //tiempo entre cada disparo (0.8s)
class Game;
class Cannon
{
private:
	Point2D<int> pos;
	Texture* textura;
	Game* game;
	int lifes;
	int remainingTime;
	Vector2D<int> moveDirection;
	bool isMoving;
	Uint32 shootCounter;
	bool canShoot;
	SDL_Rect* rect;
	
	
public:
	Cannon(Point2D<int>& _pos, Texture* _textura, Game* _game);
	void render();
	bool update(const Uint32 deltaTime);
	void hit();
	void handleEvents(const SDL_Event &event);
	SDL_Rect* getRect() { return rect; }

};

