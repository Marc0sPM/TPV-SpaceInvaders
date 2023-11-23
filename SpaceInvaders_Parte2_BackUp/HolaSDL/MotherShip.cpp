#include "MotherShip.h"


MotherShip::MotherShip(Game* _game, int _alienCont) : GameObject(_game), alienCont(_alienCont){}

bool MotherShip::shouldMove() {
	if (timeCounter < timeToMove) {
		timeCounter += FRAME_DELAY; // FRAME_DELAY = DELTA_TIME
		return false;
	}
	else {
		timeCounter = 0;
		return true;
	}
}
void MotherShip::alienDied() {
	alienCont--;
}

void MotherShip::cannotMove() {
	cantMove = true;
	aliensDirection = aliensDirection * -1;
	timeToMove -= ALIEN_INCREMENT_SPEED;
	cantMove = false;

}
void MotherShip::alienLanded() {
	landed = true;
}
void MotherShip::update() {

}
