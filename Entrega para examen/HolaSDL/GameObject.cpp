#include "checkML.h"
#include "GameObject.h"
#include "Game.h"



GameObject::GameObject(Game* game): game(game){}

GameObject::~GameObject(){}

void GameObject::setListAnchor(GameList<GameObject, true>::anchor objAnchor) {
	listAnchor = objAnchor;
}