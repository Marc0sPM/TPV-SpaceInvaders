#include "Mothership.h"

Mothership::Mothership(Game* _game) : alienCont(0), GameObject(_game) { }
void Mothership::update() {
	
	//Moviemiento intermitente de los aliens
	if (timeCounter < timeToMove) {
		
		timeCounter += DELTA_TIME;
		

		/*if (shouldmove && canMove) timeToMove -= 50;*/
		shouldmove = false;
	}
	else{
		//cuando los aliens se mueven de verdad
		timeCounter = 0;
		shouldmove = true;
		if (!canMove) {
			state = goDown;
			canMove = true;
		}
		else state = Moving;
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
void Mothership::cannotMove() {
	if (canMove && !shouldmove) {
		aliensDirection = aliensDirection * -1;
	}
	
	canMove = false;
}
//Si va hacia abjo devuelve el offset si no, 0
int Mothership::getVerticalOffset() {
	if (state == goDown) return VERTICAL_OFFSET;
	else return 0;
}
void Mothership::setState(MovingStates _state) {
	state = _state;
}

