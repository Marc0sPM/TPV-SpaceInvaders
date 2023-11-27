#include "Bunker.h"


using namespace std;
//Constructora
Bunker::Bunker(Game* _game, Point2D<int>& _pos, int _lifes, Texture* _textura) :

	textura(_textura),
	SceneObject(_game, _pos, _lifes, _textura->getFrameWidth(), _textura->getFrameHeight()) {
	currentFrame = 0;
	lifePercentage = 100;
	rect = new SDL_Rect{ pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	maxLife = lifes;
}

void Bunker::render() const {
	*rect = { pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(*rect, 0, currentFrame);
}
void Bunker::update() {
	//Ver luego me da pereza, funciona bien detallitos
	currentFrame = maxLife - lifes;
}


bool Bunker::hit(SDL_Rect* otherRect, char otherSrc) {
	
	return SceneObject::hit(otherRect, otherSrc);
}

