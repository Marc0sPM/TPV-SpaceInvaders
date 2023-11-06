#include "Laser.h"
#include "Game.h"

Laser::Laser(Point2D<int>& _pos, bool _src, SDL_Renderer* _renderer, Game* _game) :
	pos(_pos), src(_src), renderer(_renderer), game(_game) {
}

void Laser::render() {
	SDL_Rect rect = { pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };
    color color;
    if (src) color = { 0, 0, 255, 255 }; //color setted blue -> from aliens
    else color = { 255, 0, 0, 255 };//color setted red -> from cannon
	SDL_SetRenderDrawColor(renderer,color.r, color.g, color.b, color.alpha );
	SDL_RenderFillRect(renderer, &rect);
}
bool Laser::update( Cannon* cannon) {
	//src == true -> alien
    if (src) {
        //MOVIMIENTO LASER
        pos = pos + LASER_SPEED;
        //CONLISION CON PLAYER
        if (pos.getX() + LASER_WIDTH >= cannon->getPos().getX() &&
            pos.getX() <= cannon->getPos().getX() + cannon->getTexture()->getFrameWidth() &&
            pos.getY() + LASER_HEIGHT >= cannon->getPos().getY() &&
            pos.getY() <= cannon->getPos().getY() + cannon->getTexture()->getFrameHeight()) {
            cannon->hit();
            return false;
        }

        //COLISION CON BUNKERS
        return bunkerColision(game->getBunkers());
    }
	//src == false -> cannon
    else {
        //MOVIMIENTO LASER
        pos = pos - LASER_SPEED;

        //COLSIION CON ALIENS
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
        //COLISION CON BUNKERS
        return bunkerColision(game->getBunkers());
    }
}
bool Laser::bunkerColision(const vector<Bunker*> bunkers) {
    for (int i = 0; i < bunkers.size(); i++) {
        Bunker* bunker = bunkers[i];
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