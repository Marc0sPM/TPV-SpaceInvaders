#include "Laser.h"
#include "Game.h"


Laser::Laser(Point2D<int>& _pos, char _src, Game* _game) : src(_src), SceneObject(_game, _pos, 1, LASER_WIDTH, LASER_HEIGHT) {
    rect = new SDL_Rect{ pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };

    renderer = game->getRenderer();
};
void Laser::render() const {
    *rect = { pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };
    color color;
    if (src == 'b') color = {0, 0, 255, 255}; //color setted blue -> from aliens
    else if(src == 'r')color = {255, 0, 0, 255};//color setted red -> from cannon
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.alpha);
    SDL_RenderFillRect(renderer, rect);
}
void Laser::update() {
    if (src == 'b')
        pos = pos + LASER_SPEED;
    else if (src == 'r') pos = pos + LASER_SPEED * -1;
    if (game->damage(rect, src)) {
        lifes--;
    }
    if (pos.getY() < 0 || pos.getY() > windowHeight) lifes--;
    SceneObject::update();
}


bool Laser::hit(SDL_Rect* otherRect, char otherSrc) {
    if (otherSrc != src) {
        return SceneObject::hit(otherRect, otherSrc);
    }
    return false;
}
void Laser::save(std::ostream& os) const {
    os << "6 " << pos.getX() << " " << pos.getY() << " " << src ;
}