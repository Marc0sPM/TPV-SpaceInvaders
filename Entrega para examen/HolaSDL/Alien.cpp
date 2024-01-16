#include "checkML.h"
#include "Mothership.h"
#include "Alien.h"
#include "Game.h"
#include "PlayState.h"
#include "Exceptions.h"
#include <cmath>


Alien::Alien(PlayState* playState,std::istream& entrada, Texture* textura, Mothership* mothership) 
	:
	SceneObject(playState,entrada), 
	textura(textura),
	mothership(mothership),
	destRect(std::make_unique<SDL_Rect>(SDL_Rect{ pos.getX(), pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() })),
	currentAnimationFrame(playState->getRandomRange(0, 1))
{
	setTexture(textura);
	if (!(entrada >> indice))throw FileFormatError("Indice de alien no valido en línea: ", 17);
}

bool Alien::hit(SDL_Rect* attackRect, char laserType) {
	if (laserType == 'b') 
		if (SceneObject::hit(attackRect, laserType)) {
			lifes--;
			mothership->alienDied();
			switch (indice) {
			case 0:
				playState->increasePunctuation(SHOOTER_POINTS);
				break;
			case 1:
				playState->increasePunctuation(GREEN_POINTS);
				break;
			case 2:
				playState->increasePunctuation(RED_POINTS);
				break;
			}
			return true;
		}
		
	return false;
}
void Alien::render() const {
		*destRect = { (int)pos.getX(), (int)pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
		textura->renderFrame(*destRect, indice, currentAnimationFrame);

}
void Alien::update() {
	if (mothership->shouldMove()) {
		pos += mothership->getDirection();
		playAnimation();

		if ((pos.getX() <= ALIEN_SPEED
			&& mothership->getDirection().getX() < 0)
			|| (pos.getX() > WINDOW_WIDTH - (textura->getFrameWidth() + ALIEN_SPEED)
				&& mothership->getDirection().getX() > 0))
		{
			mothership->cannotMove();
		}

		if (pos.getY() >= playState->getCannonPosY()) mothership->alienLanded();
		
	}
	SceneObject::update();
}
void Alien::playAnimation(){
	if (currentAnimationFrame == 0) currentAnimationFrame = 1;
	else currentAnimationFrame = 0;
	cout << currentAnimationFrame << endl;
}

void Alien::save(ostream& os) const {
	
	os << "1 " << (int)pos.getX() << " " << (int)pos.getY() << " " << indice << endl;
};
SDL_Rect* Alien::getRect()const {
	return destRect.get();
}

