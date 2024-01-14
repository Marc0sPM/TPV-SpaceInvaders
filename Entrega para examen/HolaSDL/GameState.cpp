#include "GameState.h"
void GameState::addEventListener(EventHandler* listener) {
	eventListeners.push_back(listener);
}
void GameState::addObject(GameObject* object) {
	gameObjects.push_back(object);
}
GameState::~GameState() {
	delete game;
	for (auto& it : eventListeners) {
		delete it;
	}
}