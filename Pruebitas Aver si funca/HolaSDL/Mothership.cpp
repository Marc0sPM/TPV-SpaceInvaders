#include "Mothership.h"

Mothership::Mothership(Game* _game) : alienCont(0), GameObject(_game){}
void Mothership::update() {
	if (timeCounter < timeToMove) {
		timeCounter += DELTA_TIME;
		shouldmove = false;
	}
	else {
		timeCounter = 0;
		shouldmove = true;
	}
}
void Mothership::render() const{
	
}
void Mothership::addAlien() {
	alienCont++;
}
bool Mothership::shouldMove() {
	return shouldmove;
	
}