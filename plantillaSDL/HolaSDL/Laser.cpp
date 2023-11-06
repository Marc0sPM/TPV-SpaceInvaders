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
bool Laser::update(const vector<Alien*>& aliens, const vector<Bunker*>& bunkers, const vector<Laser*>& lasers,  Cannon* cannon) {
	
    if (canSelfDestroy) return false;
    //src -> alien
    if (src) {
        pos = pos + LASER_SPEED;
        
        if (pos.getY() > windowHeight || cannonColision(cannon)) return false;
    }
	//src -> cannon
    else {
        pos = pos - LASER_SPEED;

        if (pos.getY() < 0 ||
            alienColision(aliens) || laserColision(lasers, true)) return false;

    }
    if (laserColision(lasers, !src))  return false;
    return bunkerColision(bunkers);
}


bool Laser::bunkerColision(const vector<Bunker*>& bunkers) {
    for (int i = 0; i < bunkers.size(); i++) {

        if (SDL_HasIntersection(bunkers[i]->getRect(), rect)) {
            bunkers[i]->hit();
            return false;
        }
    }
    return true;
}
bool Laser::alienColision(const vector<Alien*>& aliens) {
    for (int i = 0; i < aliens.size(); i++) {

        if (SDL_HasIntersection(aliens[i]->getRect(), rect)) {
            aliens[i]->hit();
            return true;
        }
    }
    return false;
}
bool Laser::cannonColision(Cannon* cannon) {
    if (SDL_HasIntersection(cannon->getRect(), rect)) {
        cannon->hit();
        return true;
    }
    return false;
}
bool Laser::laserColision(const vector<Laser*>& lasers,bool srcOpposite) {
    for (int i = 0; i < lasers.size(); i++) {
        if (SDL_HasIntersection(lasers[i]->getRect(), rect) && lasers[i]->getSource() == srcOpposite) {
            lasers[i]->setSelfDestroy();
            return true;

        }
    }
    return false;

}
bool Laser::getSource() { return src; }
SDL_Rect* Laser::getRect() { return rect; }
void Laser::setSelfDestroy() {
    canSelfDestroy = true;
}