#include "GameState.h"
void GameState::addEventListener(EventHandler* listener) {
	eventHandlers.push_back(listener);
}
void GameState::addObject(GameObject* object) {
	gameObjects.push_back(object);
}