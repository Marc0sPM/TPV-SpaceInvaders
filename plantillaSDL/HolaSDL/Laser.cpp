#include "Laser.h"
#include "Game.h"

Laser::Laser(Point2D<int>& _pos, bool _src, SDL_Renderer* _renderer, Game* _game) :
	pos(_pos), src(_src), renderer(_renderer), game(_game) {
}

void Laser::render() {
	SDL_Rect rect = { pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}
bool Laser::update() {
	//src == true -> alien
    if (src) {
        pos = pos + LASER_SPEED;
    }
	//src == false -> cannon
    else {
        pos = pos - LASER_SPEED;
        for (int i = 0; i < game->getAliens().size(); i++) {
            Alien* alien = game->getAliens()[i];
            Point2D<int> alienPos = alien->getPos();
            int alienWidth = alien->getTexture()->getFrameWidth();
            int alienHeight = alien->getTexture()->getFrameHeight();

            if (pos.getX() + LASER_WIDTH >= alienPos.getX() && pos.getX() <= alienPos.getX() + alienWidth &&
                pos.getY() + LASER_HEIGHT >= alienPos.getY() && pos.getY() <= alienPos.getY() + alienHeight) {

                alien->hit();
                return false;
            }
        }
    }
    
    for (int i = 0; i < game->getBunkers().size(); i++) {
        Bunker* bunker = game->getBunkers()[i];
        Point2D<int> bunkerPos = bunker->getPos();
        int bunkerWidth = bunker->getTexture()->getFrameWidth();
        int bunkerHeight = bunker->getTexture()->getFrameHeight();
        

        if (pos.getX() + LASER_WIDTH >= bunkerPos.getX() && pos.getX() <= bunkerPos.getX() + bunkerWidth &&
            pos.getY() + LASER_HEIGHT >= bunkerPos.getY() && pos.getY() <= bunkerPos.getY() + bunkerHeight) {
            // El láser ha chocado con el bunker
           

            // Reducir la vida del bunker y eliminar el láser
            bunker->hit();
            return false;
        }
    }
	return true;
}