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
			isMoving = true;
			moveDirection = { -1, 0 };
			break;
		case SDLK_d:
			isMoving = true;
			moveDirection = { 1, 0 };
			break;
		}
		if (event.key.keysym.sym == SDLK_SPACE) {
			Point2D<int> centeredPos(pos.getX() + textura->getFrameWidth() / 2,
				pos.getY() - textura->getFrameHeight());

			game->fireLaser(centeredPos, false);
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_a:
		case SDLK_d:
			isMoving = false;
			moveDirection = { 0, 0 };
			break;
		}
	}
			
		
}
Point2D<int> Cannon::getPos() { return pos; }