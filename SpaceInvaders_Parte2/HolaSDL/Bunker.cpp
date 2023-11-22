#include "Bunker.h"


using namespace std;
//Constructora
//Bunker::Bunker() : game(), pos(), lifes(), textura(), {}
Bunker::Bunker(Game* _game, Point2D<int>& _pos, int _lifes, Texture* _textura) :
	
	textura(_textura) ,
	SceneObject(_game, _pos, _lifes, textura->getFrameWidth(), textura->getFrameHeight()) {
	currentFrame = 0;
	lifePercentage = 100;
	rect = new SDL_Rect{ pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
}

void Bunker:: render() const{
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

