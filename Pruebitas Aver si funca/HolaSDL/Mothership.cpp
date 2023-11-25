#include "Mothership.h"

Mothership::Mothership(Game* _game) : alienCont(0), GameObject(_game){}
void Mothership::update() {
	//Moviemiento intermitente de los aliens
	if (timeCounter < timeToMove) {
		timeCounter += DELTA_TIME;
		shouldmove = false;
		if (!canMove) canMove = true;
	}
	else {
		timeCounter = 0;
		shouldmove = true;
	}
	//Comprobacion de direccion
	
}
void Mothership::render() const{
	
}
void Mothership::addAlien() {
	alienCont++;
}
bool Mothership::shouldMove() {
	return shouldmove;
}
void Mothership::cannotMove() {
	if (canMove && !shouldmove) {
		aliensDirection = aliensDirection * -1;
	}
	canMove = false;
}

