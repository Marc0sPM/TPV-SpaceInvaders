#include "ShooterAlien.h"

ShooterAlien::ShooterAlien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo, int _reloadTime, MotherShip* _motherShip)
	: 
	reloadTime(_reloadTime),
	Alien(_game, _pos, _textura, _subtipo, _motherShip) {}

void ShooterAlien::update() {


	//logica de disparo que hay que ver para que funcione

	//SE QUITA LA COMPROBACION DE TIPO PORQUE SOLO LOS ALIENS SHOOTERS VAN A SER DE ESTA CLASE
	if (game->getRandomRange(0, 2000) == 1) { 
		Point2D<int> centeredPos(pos.getX() + textura->getFrameWidth() / 2,
			pos.getY());

		game->fireLaser(centeredPos, true); //cambiar firelaser
	}

	Alien::update(); //retorna el update de alien para el movimiento
}