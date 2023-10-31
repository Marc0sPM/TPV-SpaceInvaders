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
void Cannon::update() {
	if(isMoving)
	 pos = pos + moveDirection * SPEED;
}
void Cannon::hit() {
	lifes--;
}
void Cannon::handleEvents(const SDL_Event &event) {
	
		if (event.type == SDL_KEYDOWN) {
			isMoving = true;
			switch (event.key.keysym.sym) {
			case SDLK_a:
				moveDirection = { -1, 0 };
					break;
			case SDLK_d:
				moveDirection = { 1, 0 };
					break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			isMoving = false;
			moveDirection = { 0, 0 };
			
		}
	
	
	
	
}