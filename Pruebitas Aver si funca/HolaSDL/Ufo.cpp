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
		texture->renderFrame(*rect, 0, 1);
	}
}
void Ufo::update() {
	// Logica de movimiento

	switch (state) {
	case SHOWN:
		pos = pos + direction * UFO_SPEED;
		checkLimits();
		break;
	case HIDE:
		if (timeCont < randomShownTime) {
			timeCont += FRAME_DELAY;
			std::cout << timeCont << std::endl;
		}
		else {
			timeCont = 0;
			if (state == HIDE) {
				canShow();
			}
		}
		break;
	case DEAD:
		cout << "Muerto";
		if (deadFramesCont < DEAD_FRAMES * FRAME_DELAY) {
			deadFramesCont += FRAME_DELAY;
		}
		else {
			deadFramesCont = 0;
			pos = initialPos;
			state = HIDE;
		}
		break;
	}

}
	/*if (state == SHOWN) {
		pos = pos + direction * UFO_SPEED;
		checkLimits();
	}
	if (timeCont < randomShownTime) {
		timeCont += FRAME_DELAY;
		cout << timeCont << endl;
	}
	else {
		timeCont = 0;
		if (state == HIDE) {
			canShow();
		}
		if (state == DEAD) {
			if (deadFramesCont < DEAD_FRAMES) {
				deadFramesCont++;
			}
			else {
				deadFramesCont = 0;
				pos = initialPos;
				state = HIDE;
			}
		}*/
		

void Ufo::checkLimits() {
	if (pos.getX() <= UFO_SPEED) {
		pos = initialPos;
		state = HIDE;
	}
	
}
void Ufo::canShow() {
	if (game->getRandomRange(0, 1500) < 2) state = SHOWN;
}
bool Ufo::hit(SDL_Rect* otherRect, char otherSrc) {
	if (state == SHOWN) {
		if (otherSrc == 'r') {
			if (SceneObject::hit(otherRect, otherSrc)) {
				state = DEAD;
				lifes++;
				return true;
			}
		}
	}
	return false;
}
