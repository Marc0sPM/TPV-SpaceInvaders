#include "checkML.h"
#include "Mothership.h"
#include "Alien.h"
#include "Game.h"
#include "PlayState.h"
#include "Exceptions.h"


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
void Alien::Down() {
	pos.setY(pos.getY() + 10);
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
	if (textura) {
		*destRect = { (int)pos.getX(), (int)pos.getY(), textura->getFrameWidth(), textura->getFrameHeight() };
		textura->renderFrame(*destRect, indice, currentAnimationFrame);
	}
}
void Alien::update() {
	if (mothership->getState() == Moving) {
		if ((pos.getX() <= ALIEN_SPEED
			&& mothership->getDirection().getX() < 0)
			|| (pos.getX() > WINDOW_WIDTH - (textura->getFrameWidth() + ALIEN_SPEED)
				&& mothership->getDirection().getX() > 0))

			mothership->cannotMove();
	}

	if (mothership->shouldMove()) {
		//Evaluamos salto
		pos = pos + Point2D<int>(0, mothership->getVerticalOffset());
		if (mothership->getState() == Moving)
			pos = pos + (mothership->getDirection() * mothership->getAlienSpeed());
	}
	if (pos.getY() >= playState->getCannonPosY()) mothership->alienLanded();
	playAnimation();
	SceneObject::update();
	
}
void Alien::playAnimation(){
	int time = SDL_GetTicks();
	if (time - animationTime >= 500) {
		currentAnimationFrame = 1 - currentAnimationFrame;
		animationTime = time;
	}
}

void Alien::save(ostream& os) const {
	
	os << "1 " << (int)pos.getX() << " " << (int)pos.getY() << " " << indice << endl;
};
SDL_Rect* Alien::getRect()const {
	return destRect.get();
}

