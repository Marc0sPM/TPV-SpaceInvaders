#include "Cannon.h"
#include "Game.h"
Cannon::Cannon(Point2D<int>& _pos, Texture* _textura, Game* _game) :
	pos(_pos), textura(_textura), game(_game) {
	lifes = 3;
	remainingTime = 1;
	moveDirection = { 0,0 };
	bool isMoving = false;
	
	
}
void Cannon::render(){
	SDL_Rect rect = { pos.getX(), pos.getY(),
		textura->getFrameWidth(), textura->getFrameHeight() };
	textura->render(rect);
}
bool Cannon::update() {
	 pos = pos + moveDirection * SPEED;
	return lifes > 0;
}
void Cannon::hit() {
	lifes--;
}
void Cannon::handleEvents(const SDL_Event &event) {
	
		if (event.type == SDL_KEYDOWN) {
			
			switch (event.key.keysym.sym) {
			case SDLK_a:
				/*if(pos >= 50)*/
				moveDirection = { -1, 0 };
					break;
			case SDLK_d:
				/*if(pos < windowWidth - 100)*/
				moveDirection = { 1, 0 };
					break;
			case SDLK_SPACE:
				Point2D<int> centeredPos(pos.getX() + textura->getFrameWidth() / 2, 
					pos.getY() - textura->getFrameHeight());

				game->fireLaser(centeredPos, false);
					break;
			}
			
		}
		else if (event.type == SDL_KEYUP) {
			
			moveDirection = { 0, 0 };
			
		}
}
Point2D<int> Cannon::getPos() { return pos; }