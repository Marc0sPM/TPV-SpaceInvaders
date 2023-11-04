#include "Laser.h"


Laser::Laser(Point2D<int>& _pos, bool _src, SDL_Renderer* _renderer) :
	pos(_pos), src(_src), renderer(_renderer) {
}

void Laser::render() {
	SDL_Rect rect = { pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}
bool Laser::update() {
	//src == true -> alien
	if (src) pos = pos + LASER_SPEED;
	//src == false -> cannon
	else pos = pos - LASER_SPEED;
	return true;
}