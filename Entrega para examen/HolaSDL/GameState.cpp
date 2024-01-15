#include "checkML.h"
#include "GameState.h"


GameState::GameState(Game* _game) : game(_game){}

void GameState::addEventListener(EventHandler* listener) {
	eventHandlers.push_back(listener);
}
void GameState::addObject(GameObject* object) {
	gameObjects.push_back(object);
}

SDL_Window* GameState::createMessageWindow() {
	SDL_Window* window = SDL_CreateWindow("LoadGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		MESSAGE_WINDOW_WIDTH, MESSAGE_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) throw SDLError("Fallo al cargar la ventana");
} 
