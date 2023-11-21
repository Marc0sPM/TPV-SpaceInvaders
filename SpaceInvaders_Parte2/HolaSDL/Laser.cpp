#include "Laser.h"
#include "Game.h"

Laser::Laser(Point2D<int>& _pos, bool _src, SDL_Renderer* _renderer, Game* _game) :
	pos(_pos), src(_src), renderer(_renderer), game(_game) {
    rect = new SDL_Rect{ pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };
    canSelfDestroy = false; //En caso de chocar con otro laser
    
}

void Laser::render()  {
	*rect = { pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };
    color color;
    if (src) color = { 0, 0, 255, 255 }; //color setted blue -> from aliens
    else color = { 255, 0, 0, 255 };//color setted red -> from cannon
	SDL_SetRenderDrawColor(renderer,color.r, color.g, color.b, color.alpha );
	SDL_RenderFillRect(renderer, rect);
}
bool Laser::update() {
	
    if (canSelfDestroy) return false;
    //src -> alien
    if (src) {
        pos = pos + LASER_SPEED;
        
        if (pos.getY() > windowHeight || game->cannonColision(rect)) return false;
    }
	//src -> cannon
    else {
        pos = pos - LASER_SPEED;

        if (pos.getY() < 0 ||
            game->alienColision(rect)) return false;

    }
    return (game->bunkerColision(rect) && !game->laserColision(rect, !src));
}

void Laser::setSelfDestroy() {
    canSelfDestroy = true;
}