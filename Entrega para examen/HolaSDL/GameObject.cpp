#include "GameObject.h"
#include "Game.h"
#include "checkML.h"


GameObject::GameObject(Game* _game) : game(_game) {}

GameObject::~GameObject() {}
void GameObject::setGameObjectAnchor(GameList<GameObject, true>::anchor objAnchor) {
	anchor = objAnchor;
}