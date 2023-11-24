#include "Mothership.h"

Mothership::Mothership(Game* _game) : alienCont(0), GameObject(_game){}
void Mothership::update() {
	if (alienCont == 0) alienCont = 0;
}
void Mothership::render() const{
	std::cout << "ok";
}
void Mothership::addAlien() {
	alienCont++;
}