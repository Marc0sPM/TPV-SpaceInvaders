#pragma once

#include "Vector2D.h"
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const Uint32 LASER_WIDTH = 5;
const Uint32 LASER_HEIGHT = 40;
const Vector2D<int> LASER_SPEED(0, 1);
class Laser
{
private:
	Point2D<int> pos; 
	
	bool src; //true -> alien | false->cannon
	SDL_Renderer* renderer;
public:
	Laser(Point2D<int>& pos, bool src, SDL_Renderer* renderer);
	void render();
	void update();
	 


};

