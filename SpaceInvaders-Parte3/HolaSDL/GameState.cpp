#include "GameState.h"
GameState::GameState(){}
GameState::GameState(Game* _game) : game(_game){}

void GameState::addEventListener(EventHandler* listener) {
	eventHandles.push_back(listener);
}

void GameState::addObject(GameObject* gameObject) {
	gameList.push_back(gameObject);
}
