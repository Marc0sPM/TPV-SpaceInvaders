#include "checkML.h"
#include "Cannon.h"
#include "Game.h"
#include "PlayState.h"

Cannon::Cannon(PlayState* playState, std::istream& entrada, Texture* texture) 
    :
    SceneObject(playState,entrada),
    texture(texture),
    rect(std::make_unique<SDL_Rect>(SDL_Rect{pos.getX(),pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() })),
    currentMovement(Point2D<int>(0, 0)),
	isShoot (false){
    setTexture(texture);
    if (!(entrada >> lifes) || lifes < 0)
        throw FileFormatError("error al leer las vidas del cañon", 13);
    if(!(entrada >> remainingTime))throw FileFormatError("error al leer el intervalo de disparo", 15);
};

void Cannon::render() const {
	if (texture) {
        
        *rect = { pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
        if (hasShield) {
            Texture* aux = game->getTexture(TextureName::SHIELD);
            SDL_Rect shieldRect = { pos.getX() - 4, pos.getY() - aux->getFrameHeight() / 4, aux->getFrameWidth(), aux->getFrameHeight() };
            aux->render(shieldRect);
        }
        texture->render(*rect);
	}
}
void Cannon::update() {
	pos += currentMovement * CANNON_SPEED;
        if (pos.getX() <= 0) pos.setX(1);
        else if (pos.getX() > WINDOW_WIDTH - texture->getFrameWidth())
            pos.setX(WINDOW_WIDTH - texture->getFrameWidth());
    SceneObject::update();
}
void Cannon::save(std::ostream& os) const {
    os << "0 " << pos.getX() << " " << pos.getY() << " " << lifes << " 0" <<endl;
};
bool Cannon::hit(SDL_Rect* attackRect, char laserType)
{
     if(laserType == 'r' || laserType == 'c')
         if (SceneObject::hit(attackRect, laserType)) {
             if (hasShield) hasShield = false;
             else {
                 lifes--;
             }
             return true;
         }
     return false;
}
int Cannon::getTime() const {
    return remainingTime;
}
void Cannon::setTime(int newTime) {
    remainingTime = newTime;
}
void Cannon::setShield() {
    hasShield = true;
}
void Cannon::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            currentMovement.setX(-1);  // Mover hacia la izquierda
            break;
        case SDLK_RIGHT:
            currentMovement.setX(1);  // Mover hacia la derecha
            break;
        case SDLK_SPACE:
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - remainingTime >= 500) {
                Point2D<int> aux = { pos.getX() + texture->getFrameWidth() / 2, pos.getY() };
                playState->fireLaser(aux,'b');
                remainingTime = currentTime;
            }
            break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
        case SDLK_RIGHT:
            currentMovement.setX(0);  // Dejar de moverse al soltar las teclas de dirección
            break;
        case SDLK_SPACE:

            break;
        default:
            break;
        }
    }
}

