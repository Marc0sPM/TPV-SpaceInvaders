#include "Alien.h"

Alien::Alien() : pos(), textura(), subtipo(), game() {}
Alien::Alien(Point2D<int>& _pos, Texture* _textura, int _subtipo, Game* _game): 
	pos(_pos),
	textura(_textura),
	subtipo(_subtipo),
	game(_game) {
	alive = true;
}

void Alien::render()const {
	SDL_Rect alienRect = { pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(alienRect, subtipo, 0);
}
bool Alien::update() {
	//movimiento es algo asi: 
	/* game.getDirection(); ----> sirve para que se muevan solo en una direccion, no se como
	game.getRandomRange(); -----> sirve para numero random para disparo
	*/
	//pos += game->getDirection(); //sobrecarga ya hecha y supongo que con eso se moveran los aliens
	

	return alive;
}
void Alien::hit() {
	alive = false;
}
