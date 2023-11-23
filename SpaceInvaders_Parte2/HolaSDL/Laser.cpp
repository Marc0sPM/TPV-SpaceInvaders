#include "Laser.h"
#include "Game.h"

Laser::Laser(Point2D<int>& _pos, char _src, Game* _game) :

    src(_src),
    SceneObject(_game, _pos, 1, LASER_WIDTH, LASER_HEIGHT) {
    rect = new SDL_Rect{ pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };
    canSelfDestroy = false; //En caso de chocar con otro laser
    renderer = game->getRenderer();
}

void Laser::render() const {
    *rect = { pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };
    color color;
    if (src) color = { 0, 0, 255, 255 }; //color setted blue -> from aliens
    else color = { 255, 0, 0, 255 };//color setted red -> from cannon
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.alpha);
    SDL_RenderFillRect(renderer, rect);
}
void Laser::update() {

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