#include "Bunker.h"


using namespace std;
//Constructora
Bunker::Bunker() : pos(), lifes(), textura() {}
Bunker::Bunker(Point2D<int>& _pos, int _lifes, Texture* _textura) :
	pos(_pos),
	lifes(_lifes),
	textura(_textura) {
	currentFrame = 0;
	lifePercentage = 100;
	rect = new SDL_Rect{ pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() }; 
}

void Bunker:: render() {
	*rect = {pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight()};
	textura->renderFrame(*rect, 0 , currentFrame); 
}
bool Bunker::update() {
	return lifes > 0;
}


void Bunker::hit() {
	currentFrame++;
	lifes--;
}

