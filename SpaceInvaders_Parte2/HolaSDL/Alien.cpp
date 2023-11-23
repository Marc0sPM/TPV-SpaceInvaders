#include "Alien.h"
#include "Game.h"

Alien::Alien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo, MotherShip* _motherShip) :
	textura(_textura),
	subtipo(_subtipo),
	SceneObject(game, _pos, 1, _textura->getFrameWidth(), _textura->getFrameHeight()),

	motherShip(_motherShip)
{
	rect = new SDL_Rect{ pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
}
Point2D<int> Alien::getPos()const {
	return pos;
}

void Alien::render() const { //no funca el rect
	*rect = { pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(*rect, subtipo, 0);
}
void Alien::update() {


	if (motherShip->shouldMove()) pos = pos + (motherShip->getDirection() * ALIEN_SPEED);
	if (pos.getX() <= ALIEN_SPEED ||
		pos.getX() > windowWidth - (textura->getFrameWidth() + ALIEN_SPEED)) {
		motherShip->cannotMove();
		// pos = { pos.getX(), pos.getY() + ALIEN_VERTICAL_SHIFT}; 
		//NO SE COMO HACER EL DESPLAZAMIENTO HACIA ABAJO DEL ALIEN PARA QUE SEA GLOBAL Y NO SOLO AFECTE A UNO

	}
	if (lifes <= 0) {
		motherShip->alienDied();
		game->hasDied(listIterator);

	}
}
void Alien::hit(SDL_Rect attackRect, bool src) {
	//POR DETERMINAR QUE VA AQUI 
}


