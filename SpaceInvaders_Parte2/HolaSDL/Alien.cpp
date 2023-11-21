#include "Alien.h"
#include "Game.h"
Alien::Alien() : pos(), textura(), subtipo(), game() {}
Alien::Alien(Point2D<int>& _pos, Texture* _textura, int _subtipo, Game* _game) :
	pos(_pos),
	textura(_textura),
	subtipo(_subtipo),
	game(_game),
	moveCounter(0){
	alive = true;
	rect = new  SDL_Rect{ pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
}
Point2D<int> Alien::getPos()const {
	return pos;
}

void Alien::render() {
	*rect ={ pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(*rect, subtipo, 0);
}
bool Alien::update() {
	const Uint32 deltaTime = 9; //no se si se usara esto en elgun momento (aqui esta mal)

	if (moveCounter < MOVE_INTERVAL) {
		moveCounter += deltaTime;
	}
	else {
		pos = pos + (game->getDirection() * ALIEN_SPEED);
		if (pos.getX() <=  ALIEN_SPEED ||
			pos.getX() > windowWidth - (textura->getFrameWidth() + ALIEN_SPEED))
			game->cannotMove();
		moveCounter = 0;
	}
		
	
	return alive; 
}
void Alien::hit() {
	alive = false;
}


