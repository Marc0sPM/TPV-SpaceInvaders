#include "ShooterAlien.h"


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