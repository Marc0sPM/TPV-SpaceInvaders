#pragma once

#include "Vector2D.h"
#include "texture.h"
#include <SDL.h>
#include <SDL_image.h>

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
public:
	Cannon(Point2D<int>& _pos, Texture* _textura, Game* _game);
	void render();
	void update();
	void hit();
	void handleEvents(const SDL_Event &event);


};

