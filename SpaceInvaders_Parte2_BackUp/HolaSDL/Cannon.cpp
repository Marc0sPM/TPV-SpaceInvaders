#include "Cannon.h"
#include "Game.h"
Cannon::Cannon(Point2D<int>& _pos, int _lives, int _remainingTime, Game* _game, Texture* _textura) :
SceneObject(_game, _pos, _lives, _textura->getFrameWidth(), _textura->getFrameHeight()),
textura(_textura),
remainingTime(0){
	
	moveDirection = { 0,0 };
	isMoving = false;
	shootCounter= 0;
	canShoot = true;
	rect = new SDL_Rect{ pos.getX(), pos.getY(), 
		textura->getFrameWidth(), textura->getFrameHeight() };  
}
void Cannon::render() const{
	(*rect) = {pos.getX(), pos.getY(),
		textura->getFrameWidth(), textura->getFrameHeight() };
	textura->render(*rect);
}
void Cannon::update() {

	 pos = pos + moveDirection * SPEED;
	 /*if (shootCounter < SHOOT_INTERVAL) {
		 shootCounter += deltaTime;
	 }
	 else*/ {
		 canShoot = true;
	 }
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
		if (event.key.keysym.sym == SDLK_SPACE && canShoot) {
			Point2D<int> centeredPos(pos.getX() + textura->getFrameWidth() / 2,
				pos.getY() - textura->getFrameHeight());

			game->fireLaser(centeredPos, false);
			shootCounter = 0;
			canShoot = false;
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