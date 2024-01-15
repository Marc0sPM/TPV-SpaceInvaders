#include "checkML.h"
#include "Ufo.h"
#include "Game.h"
#include "PlayState.h"


Ufo::Ufo(PlayState* playState,std::istream& entrada,Texture* _texture) :
	texture(_texture),
	SceneObject(playState, entrada),
	rect(std::make_unique<SDL_Rect>(SDL_Rect{ pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() }))
{
	int aux;
	if (!(entrada >> aux))throw FileFormatError("error al leer estado de UFO", 12);
	else state = States(aux);

	if (!(entrada >> randomShownTime))throw FileFormatError("error al leer randomShowTime de UFO", 15);

	setTexture(texture);
	
	initialPos = { WINDOW_WIDTH, pos.getY() };
};


void Ufo::render()const {
	*rect = { pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
	if (state == States::SHOWN) {
		texture->renderFrame(*rect, 0, 0);
	}
	else if (state == States::DEAD) {
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
		}
		else {
			timeCont = 0;
			canShow();
		}
		break;
	case DEAD:
		if (deadFramesCont < DEAD_FRAMES * FRAME_DELAY) {
			deadFramesCont += FRAME_DELAY;
		}
		else {
			deadFramesCont = 0;
			pos = initialPos;
			state = States::HIDE;
		}
		break;
	}
}
void Ufo::checkLimits() {
	if (pos.getX() <= UFO_SPEED) {
		pos = initialPos;
		state = HIDE;
	}
}
void Ufo::canShow() {
	if (playState->getRandomRange(0, randomShownTime) < 10) state = SHOWN;
}
bool Ufo::hit(SDL_Rect* otherRect, char otherSrc) {
	
		if (state == SHOWN && otherSrc == 'b') {
        		if (SceneObject::hit(otherRect, otherSrc)) {
    				state = States::DEAD;
				playState->increasePunctuation(UFO_POINTS);
				playState->GenerateUFOObject(pos);
				return true;
			}
		}
		return false;
}
void Ufo::save(std::ostream& os) const {
	os << "5 " << initialPos.getX() << " " << initialPos.getY() << " " << state << " " << randomShownTime<<endl;
}
