#include "checkML.h"
#include "ShooterAlien.h"
#include "Game.h"
#include "PlayState.h"
ShooterAlien::ShooterAlien(PlayState* playState,std::istream& entrada ,Texture* texture, Mothership* mothership):
	Alien(playState, entrada, texture, mothership)
	 {
     if (!(entrada >> reloadTime ))throw FileFormatError("error al leer reloadTime de shooterAlien", 8);
}
void ShooterAlien::update() {
	Alien::update();
	int currentTime = SDL_GetTicks();
	// Verifica si ha pasado suficiente tiempo desde el último disparo
	if (currentTime - reloadTime >= 1000) {
		int rnd = playState->getRandomRange(0, 2000);
		if (rnd < 2) {
			Point2D<int> aux = { pos.getX() + Alien::textura->getFrameWidth() / 2, pos.getY() };
			playState->fireLaser(aux, 'r');
			// Reinicia el contador de tiempo
			reloadTime = currentTime;
		}
	}
	
}
void ShooterAlien::save(std::ostream& os) const {
	
	os << "2 " << (int)pos.getX() << " " << (int)pos.getY() << " " <<Alien::GetIndice() <<" " <<reloadTime << endl;
}
