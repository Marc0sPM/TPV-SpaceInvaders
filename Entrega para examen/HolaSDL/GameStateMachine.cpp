#include "checkML.h"
#include "GameStateMachine.h"
GameStateMachine:: GameStateMachine() {}
GameStateMachine::~GameStateMachine() {
	while (!gameStates.empty()) {
		delete gameStates.top();
		gameStates.pop();
	}
}
void GameStateMachine::pushState(GameState* state) { 
	gameStates.push(state);
}
void GameStateMachine::popState() {
	if (!gameStates.empty()) {
		statesToDelete.push_back(gameStates.top());
		gameStates.pop();
	}
}
void GameStateMachine::replaceState(GameState* pState) {
	if (!gameStates.empty()) {
		gameStates.pop();
		gameStates.push(pState);

	}
}
void GameStateMachine::update() { 
	if (!gameStates.empty()) {
		gameStates.top()->update();
	}
} 
void GameStateMachine::render() const {
	if (!gameStates.empty()) {
		gameStates.top()->render();
	}
}
void GameStateMachine::handleEvent(const SDL_Event& event) {
	if (!gameStates.empty()) {
		gameStates.top()->handleEvent(event);
	}
	clear();
}
void GameStateMachine::clear() {
	for (auto& it : statesToDelete) {
		delete it;
		it = nullptr;
	 }
	statesToDelete.clear();
}
