#include "ShooterAlien.h"

ShooterAlien::ShooterAlien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo)
	: Alien(_game, _pos, _textura, _subtipo) {}

bool ShooterAlien::update(Uint32 deltaTime) {


	//logica de disparo que hay que ver para que funcione

	//SE QUITA LA COMPROBACION DE TIPO PORQUE SOLO LOS ALIENS SHOOTERS VAN A SER DE ESTA CLASE
	if (game->getRandomRange(0, 2000) == 1) { 
		Point2D<int> centeredPos(pos.getX() + textura->getFrameWidth() / 2,
			pos.getY());

		game->fireLaser(centeredPos, true);
	}

	return Alien::update(deltaTime); //retorna el update de alien para el movimiento
}