#include "Ufo.h"
#include "Game.h"


Ufo::Ufo(Game* _game, Point2D<int>_pos, Texture* _texture, int _randomShownTime) :
	texture(_texture),
	SceneObject(_game, _pos, 1, _texture->getFrameWidth(), _texture->getFrameHeight()),
	randomShownTime(_randomShownTime) {
	rect = new SDL_Rect{ pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
	initialPos = { windowWidth, pos.getY() };
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
	if (state == SHOWN) {
		pos = pos + direction * UFO_SPEED;
		checkLimits();
	}
	else if (state == HIDE) {
		canShow();
	}
	if (lifes <= 0)state = DEAD;
	
	if (timeCont < randomShownTime) {
		timeCont += FRAME_DELAY;
	}
	else {
		timeCont = 0;
		if(state == DEAD){
			if (deadFramesCont < DEAD_FRAMES) {
				deadFramesCont++;
			}
			else {
				deadFramesCont = 0;
				state = HIDE;
			}
		}
	}
	
	
}
void Ufo::checkLimits() {
	if (pos.getX() <= UFO_SPEED) {
		pos = initialPos;
		state = HIDE;
	}
	
}
void Ufo::canShow() {
	if (game->getRandomRange(0, 1000) < 2) state = SHOWN;
}

bool Ufo::hit(SDL_Rect* otherRect, char otherSrc) {
	if (otherSrc == 'r') return SceneObject::hit(otherRect, otherSrc);
	return false;
}
