#include "Alien.h"
#include "Game.h"

Alien::Alien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo) :
	textura(_textura),
	subtipo(_subtipo),
	SceneObject(game, _pos, 1, textura->getFrameWidth(), textura->getFrameHeight()),
	moveCounter(0){
}
Point2D<int> Alien::getPos()const {
	
	return pos;
}

void Alien::render() const{ //no funca el rect
   SDL_Rect rect = { pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(rect, subtipo, 0);
}
bool Alien::update(){  //no le metas esto Uint32 deltaTime al update porque si no no funciona el override


	//Esta logica de movimiento va en el mothership
	/*if (moveCounter < MOVE_INTERVAL) {
		moveCounter += deltaTime;
	}
	else*/ {
		pos = pos + (game->getDirection() * ALIEN_SPEED);
		if (pos.getX() <=  ALIEN_SPEED ||
			pos.getX() > windowWidth - (textura->getFrameWidth() + ALIEN_SPEED))
			game->cannotMove();
		moveCounter = 0;
	}
	return lifes > 0;
}
void Alien::hit(SDL_Rect attackRect, bool src) {
	//POR DETERMINAR QUE VA AQUI 
}


