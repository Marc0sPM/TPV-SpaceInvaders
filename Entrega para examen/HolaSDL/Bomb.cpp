#include "checkML.h"
#include "Bomb.h"

#include "Game.h"
#include "PlayState.h"

Bomb::Bomb(PlayState* playState, Texture* _texture, std::istream& entrada) 
    :
    SceneObject(playState, entrada), texture(_texture),
    rect(std::make_unique<SDL_Rect>(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), _texture->getFrameWidth(), _texture->getFrameHeight() }))
{
    setTexture(texture);
}

Bomb::Bomb(PlayState* playState, Texture* _texture, Point2D<int> pos) 
    :
    SceneObject(playState, pos, _texture->getFrameWidth(), _texture->getFrameWidth()), texture(_texture),
    rect(std::make_unique<SDL_Rect>(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), _texture->getFrameWidth(), _texture->getFrameHeight() }))
{
    lifes = BOMB_LIFES;
}


void Bomb::update() {
    pos += BOMB_SPEED;
    if (pos.getY() > 600)lifes = 0;
    if (playState->damage(rect.get(), 'c')) {
        lifes = 0;
    }
    SceneObject::update();
}

void Bomb::render() const {
    if (texture) {
        *rect = { (int)pos.getX(), (int)pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
        texture->renderFrame(*rect, 0, 0);
    }
}

bool Bomb::hit(SDL_Rect* attackRect, char laserType) {
    if (laserType == 'b') {
        if (SceneObject::hit(attackRect, laserType)) {
            lifes--;
            return true;
        }
    }
    return false;
}

void Bomb::save(std::ostream& os) const {
    // Esta mal, hay que hacerlo, era solo para rellenar
    os << "Bomb " << pos.getX() << " " << pos.getY() << " " << lifes << std::endl;
};