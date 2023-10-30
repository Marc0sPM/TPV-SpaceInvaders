#include "Cannon.h"
Cannon::Cannon(Point2D<int>& _pos, Texture* _textura, Game* _game) :
	pos(_pos), textura(_textura), game(_game) {
	lifes = 3;
	remainingTime = 1;
	moveDirection = { 0,0 };
}
void Cannon::render(){
	SDL_Rect rect = { pos.getX(), pos.getY(),
		textura->getFrameWidth(), textura->getFrameHeight() };
	textura->render(rect);
}
void Cannon::update() {

}