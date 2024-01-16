#include "checkML.h"
#include "Mothership.h"

Mothership::Mothership(Game* _game ) : GameObject(_game){ }
void Mothership::update() {
	
	//Cada TIME_TO_MOVE ms hace que se muevan
	int time = SDL_GetTicks();
	if (time - timeCounter > TIME_TO_MOVE) {
		timeCounter = SDL_GetTicks();
		shouldmove = true;
		if (jump) {
			currentDirection = jumpVector;
			jump = false;
			changeDirection = true;
		}
		else {
			if (changeDirection) {
				changeDirection = false;
				moveDirection = moveDirection * -1;
			}
			currentDirection = moveDirection;
		}
	}
	else { 
		shouldmove = false; 
	}

}
void Mothership::render() const {

}
void Mothership::addAlien() {
	alienCont++;
}
bool Mothership::shouldMove() {

	return shouldmove;
}
void Mothership::cannotMove() {
	jump = true;
	
	moveDirection += Vector2D{ SPEED_INCREMENT, 0 };
	moveDirection = moveDirection * -1;
}
void Mothership::alienDied() {
	alienCont--;
}
void Mothership::alienLanded() {
	landed = true;
}
void Mothership::save(std::ostream& os) const {

}




