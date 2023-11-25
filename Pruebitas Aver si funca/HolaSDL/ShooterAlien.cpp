#include "Game.h"
#include "ShooterAlien.h"




ShooterAlien::ShooterAlien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo, int _reloadTime, Mothership* _motherShip) 
	:
	reloadTime(_reloadTime),
	Alien(_game, _pos, _textura, _subtipo, _motherShip) {}

void ShooterAlien::update() {
	Alien::update();

	//logica de disparo que hay que ver para que funcione

	//SE QUITA LA COMPROBACION DE TIPO PORQUE SOLO LOS ALIENS SHOOTERS VAN A SER DE ESTA CLASE
	
	Point2D<int> centeredPos(pos.getX() + textura->getFrameWidth() / 2,
		pos.getY());
	

	 //retorna el update de alien para el movimiento
}