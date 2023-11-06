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
}

void Bunker:: render()const {
	SDL_Rect bunkerRect = {pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight()};
	textura->renderFrame(bunkerRect, 0 , currentFrame); 
}
bool Bunker::update() {
	return lifes > 0;
}
Texture* Bunker::getTexture() const {
	return textura;
}

void Bunker::hit() {
	currentFrame++;
	lifes--;
}
Point2D<int> Bunker:: getPos() const { return pos; }

