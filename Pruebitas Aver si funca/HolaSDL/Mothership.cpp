#include "Mothership.h"

Mothership::Mothership(Game* _game) : alienCont(0), GameObject(_game) { }
void Mothership::update() {
	
	//Moviemiento intermitente de los aliens
	if (timeCounter < timeToMove) {
		
		timeCounter += DELTA_TIME;
		

		
		shouldmove = false;
	}
	else{
		//cuando los aliens se mueven de verdad
		timeCounter = 0;
		
		shouldmove = true;
		if (!canMove) {
			state = goDown;
			timeToMove -= SPEED_INCREMENT;
			canMove = true;
		}
		else state = Moving;
		std::cout << timeToMove << std::endl;
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
void Mothership::alienDied() {
	alienCont--;
}
void Mothership::alienLanded() {
	landed = true;
}


