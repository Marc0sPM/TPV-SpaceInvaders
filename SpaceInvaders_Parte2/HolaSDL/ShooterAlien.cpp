#include "ShooterAlien.h"




bool ShooterAlien::update() {


	//logica de disparo que hay que ver para que funcione
	if (game->getRandomRange(0, 2000) == 1 && subtipo == 0) {
		Point2D<int> centeredPos(pos.getX() + textura->getFrameWidth() / 2,
			pos.getY());

		game->fireLaser(centeredPos, true);
	}

	return Alien::update(); //retorna el update de alien para el movimiento
}