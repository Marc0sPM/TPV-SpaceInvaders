#include "Mothership.h"
Mothership::Mothership(Game* _game, int _cant) : GameObject(_game), cant(_cant){}
void Mothership::update() {
	if (cant == 0) cant = 0;
}
void Mothership::render() const{
	std::cout << "ok";
}