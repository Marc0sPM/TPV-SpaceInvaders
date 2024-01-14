#include "GameObject.h"
#include "Game.h"
#include "checkML.h"


GameObject::GameObject(Game* _game) : game(_game) {}

GameObject::~GameObject() {
	delete game;
}
void GameObject::setListAnchor(GameList<GameObject, true>::anchor objAnchor) {
	an = objAnchor;
}