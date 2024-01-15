#include "checkML.h"
#include "Laser.h"
#include "Game.h"
#include "PlayState.h"
Laser::Laser(PlayState* playState, std::istream& entrada) 
    :
    SceneObject(playState, entrada),
    rect(std::make_unique<SDL_Rect>(SDL_Rect{ pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT }))
{
    if (!(entrada >> src))throw FileFormatError("error al leer source del Laser", 6);
    renderer = game->getRenderer();
}
Laser::Laser(PlayState* playState, Point2D<int>& _pos, char _src) :
    src(_src), 
    SceneObject(playState, _pos, LASER_WIDTH, LASER_HEIGHT),
    rect(std::make_unique<SDL_Rect>(SDL_Rect{ pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT }))
{
    renderer = game->getRenderer();
};
void Laser::render() const {
    
    *rect = { pos.getX(), pos.getY(), LASER_WIDTH, LASER_HEIGHT };
    color color;
    if (src == 'b') color = { 0, 0, 255, 255 }; //color setted blue -> from aliens
    else if (src == 'r')color = { 255, 0, 0, 255 };//color setted red -> from cannon
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.alpha);
    SDL_RenderFillRect(renderer, rect.get());
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

}
void Laser::update() {
    if (src == 'r')
        pos = pos + LASER_SPEED;
    else if (src == 'b') pos = pos + LASER_SPEED * -1;
    if (playState->damage(rect.get(), src)) {
        lifes--;
    }
    if (pos.getY() < 0 || pos.getY() > WINDOW_HEIGHT) lifes--;
    SceneObject::update();
}


bool Laser::hit(SDL_Rect* otherRect, char otherSrc) {
    if (otherSrc != src && otherSrc != 'c') {
        if (SceneObject::hit(otherRect, otherSrc)) {
            lifes--;
            return true;
        }
    }
    return false;
}
void Laser::save(std::ostream& os) const {
    os << "6 " << pos.getX() << " " << pos.getY() << " " << src << endl;
}