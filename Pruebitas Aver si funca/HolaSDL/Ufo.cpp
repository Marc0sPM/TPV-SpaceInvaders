#include "Ufo.h"
#include "Game.h"


Ufo::Ufo(Game* _game, Point2D<int>_pos, Texture* _texture, int _randomShownTime) :
	texture(_texture),
	SceneObject(_game, _pos, 1, _texture->getFrameWidth(), _texture->getFrameHeight()),
	randomShownTime(_randomShownTime) {
	rect = new SDL_Rect{ pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
};

void Ufo::render()const {
	if (state == SHOWN) {
		*rect = { pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
		texture->renderFrame(*rect, 0, 0);
	}
	else if (state == DEAD) {
		*rect = { pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
		texture->renderFrame(*rect, 1, 0);
	}
}
void Ufo::update() {
	// Logica de movimiento
	if (pos.getX() <= UFO_SPEED && movingState == LEFT) {
		direction = direction * -1;
		movingState = RIGHT;
	}
	else if(pos.getX() > windowWidth - (texture->getFrameWidth() + UFO_SPEED) && movingState == RIGHT){
		direction = direction * -1;
		movingState = LEFT;
	}
	cout<< pos.getX()<<endl; 
	pos = pos + direction * UFO_SPEED;
	if (timeCont < randomShownTime) {
		timeCont += FRAME_DELAY;
	}
	else {
		// muerto
		timeCont = 0;
		if (state == SHOWN) state = HIDE;
		else if (state == HIDE) state = SHOWN;
		//randomShownTime = game->getRandomRange(100, 2000);
	}
	if (lifes <= 0)state = DEAD;
	
}