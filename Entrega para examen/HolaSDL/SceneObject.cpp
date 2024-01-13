#include "SceneObject.h"
#include "Game.h"
#include "PlayState.h"

//Constructora por lectura desde entrada
SceneObject::SceneObject(PlayState* playState, std::istream& in)
	:
	GameObject(playState->getGame()),
	playState(playState)
{
	int posX, posY;
	in >> posX >> posY;
	pos = { posX, posY };
}
	
//Constructora por instancia de objecto en escena
SceneObject::SceneObject(PlayState* playState, Point2D<int> pos, int width, int height)
	:
	GameObject(playState->getGame()),
	playState(playState),
	pos(pos),
	width(width),
	height(height){}

void SceneObject::setSceneAnchor(GameList<SceneObject>::anchor anchor) {
	sceneAnchor = anchor;
}