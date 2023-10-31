#include "Alien.h"
#include "Game.h"
Alien::Alien() : pos(), textura(), subtipo(), game() {}
Alien::Alien(Point2D<int>& _pos, Texture* _textura, int _subtipo, Game* _game): 
	pos(_pos),
	textura(_textura),
	subtipo(_subtipo),
	game(_game) {
	alive = true;
	Vector2D<int> direction;

}
Point2D<int> Alien::getPos() {
	return pos;
}

void Alien::render()const {
	SDL_Rect alienRect = { pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(alienRect, subtipo, 0);
}
bool Alien::update() {
	
	
	direction = game->getDirection();
	pos = pos + (direction * ALIEN_SPEED);
	return alive;
}
void Alien::hit() {
	alive = false;
}
