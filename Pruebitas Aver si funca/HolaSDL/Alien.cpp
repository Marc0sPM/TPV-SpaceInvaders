#include "Alien.h"
#include "Game.h"

Alien::Alien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo, Mothership* _motherShip) :
	textura(_textura),
	subtipo(_subtipo),
	SceneObject(_game, _pos, 1, _textura->getFrameWidth(), _textura->getFrameHeight()),
	motherShip(_motherShip)
{
	rect = new SDL_Rect{ pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
}
Point2D<int> Alien::getPos()const {
	return pos;
}
void Alien::render() const { 
	*rect = { pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
	textura->renderFrame(*rect, subtipo, 0);
}
void Alien::update() { 
	
	if (motherShip->getState() == Moving)  { 
		if((pos.getX() <= motherShip->getAlienSpeed() 
			&& motherShip->getDirection().getX() < 0)
			|| (pos.getX() > windowWidth - (textura->getFrameWidth() + motherShip->getAlienSpeed()) 
				&& motherShip->getDirection().getX() > 0))

		motherShip->cannotMove();  
	}
	
	if(motherShip->shouldMove()) {
		//Evaluamos salto
		pos = pos + Point2D<int>(0, motherShip->getVerticalOffset());
		if(motherShip->getState() == Moving)
			pos = pos + (motherShip->getDirection() * motherShip->getAlienSpeed());
	}
	if (pos.getY() >= game->getCannonPos()) motherShip->alienLanded();
		
}
bool Alien::hit(SDL_Rect* otherRect, char otherSrc) {

	if (otherSrc == 'r') {
		if (SceneObject::hit(otherRect, otherSrc)) {
			motherShip->alienDied();
			return true;
		}
	}
	return false;
}


