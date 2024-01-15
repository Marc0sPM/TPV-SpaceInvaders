#include "checkML.h"
#include "Bunker.h"
#include "Game.h"
#include "PlayState.h"

Bunker::Bunker(PlayState* playState, std::istream& entrada, Texture* texture) :
	SceneObject(playState, entrada),
	texture(texture),
	rect(std::make_unique< SDL_Rect>(SDL_Rect{ pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() }) ){
	setTexture(texture);
	if (!(entrada >> lifes) || lifes < 0)
		throw FileFormatError("error al leer las vidas del búnker", 11);
};

void Bunker::render() const {
	if (texture) {
		*rect = { pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
		switch (lifes)
		{
		case 4: 
			texture->renderFrame(*rect, 0, 0);
			break;
		case 3:
			texture->renderFrame(*rect, 0, 1);
			break;
		case 2:
			texture->renderFrame(*rect, 0, 2);
			break;
		case 1:
			texture->renderFrame(*rect, 0, 3);
			break;
		}
		
	}
}
void Bunker::update() {
	SceneObject::update();
}
void Bunker::save(ostream& os) const {
	os << "4 " << pos.getX() << " " << pos.getY() << " " << lifes << endl;
};
bool Bunker::hit(SDL_Rect* attackRect, char laserType) {
	if (SceneObject::hit(attackRect, laserType)) {
		lifes--;
		return true;
	}
}
SDL_Rect* Bunker::getRect() const{
	return rect.get();
}
