#include "checkML.h"
#include "SceneObject.h"
#include "Game.h"
#include "PlayState.h"
SceneObject::SceneObject(PlayState* playState,std::istream& entrada)
    : GameObject(playState->getGame()), playState(playState){
    int x, y;
    entrada >> x >> y;
    pos = {x ,y };
}
SceneObject::SceneObject(PlayState* playState, Point2D<int>& pos, int width, int height) : 
    pos(pos), 
    playState(playState),
    width(width),
    height(height),
    GameObject(playState->getGame()){}

SceneObject::~SceneObject(){}
bool SceneObject::hit(SDL_Rect* attackRect, char laserType) {
    SDL_Rect rect = { pos.getX(), pos.getY(), width, height };
    return SDL_HasIntersection(attackRect, &rect);
}
void SceneObject::setListAnchor(GameList<SceneObject>::anchor anchor) {
    sceneAnchor = anchor;
}
void SceneObject::update() {
    if (lifes <= 0) {
        playState->hasDied(sceneAnchor);
    }
}
void SceneObject::render()const {}
void SceneObject::save(std::ostream& os) const {}
void SceneObject::setTexture(Texture* texture) {
    width = texture->getFrameWidth();
    height = texture->getFrameHeight();
}
