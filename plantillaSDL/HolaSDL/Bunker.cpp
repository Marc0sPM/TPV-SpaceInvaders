#include "Bunker.h"


using namespace std;
//Constructora
Bunker::Bunker() : pos(), lifes(), textura() {}
Bunker::Bunker(Point2D<int>& _pos, int _lifes, Texture* _textura) :
	pos(_pos),
	lifes(_lifes),
	textura(_textura) {
	maxLife = lifes;
	currentFrame = 0;
	lifePercentage = 100;
}

void Bunker:: render()const {
	SDL_Rect bunkerRect = {pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight()};
	textura->renderFrame(bunkerRect, 0 , currentFrame); 
}
bool Bunker::update() {
	//Al haber 4 frames del bunker, este se actualizan cada 25% de vida
	if ((lifes * 100) / maxLife < lifePercentage - 25 && lifes > 0) { //cambiar a 4 vidas
		currentFrame++;
		lifePercentage -= 25;
	}
	
	return lifes > 0;
}
Texture* Bunker::getTexture() const {
	return textura;
}

void Bunker::hit() {
	lifes--;
}
Point2D<int> Bunker:: getPos() { return pos; }

