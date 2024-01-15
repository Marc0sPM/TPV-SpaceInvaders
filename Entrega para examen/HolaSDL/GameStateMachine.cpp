#include "checkML.h"
#include "GameStateMachine.h"
GameStateMachine:: GameStateMachine() {}

void GameStateMachine::pushState(std::shared_ptr<GameState> pState) {
	gameStates.push(pState);
}
void GameStateMachine::popState() {
	if (!gameStates.empty()) {
		gameStates.pop();
	}
}
void GameStateMachine::replaceState(std::shared_ptr<GameState> pState) {
	if (!gameStates.empty()) {
		gameStates.pop();
		gameStates.push(pState);

	}
}
void GameStateMachine::update() { 
	if (!gameStates.empty()) {
		std::shared_ptr<GameState> currentState = gameStates.top();
		currentState->update();
	}
} 
void GameStateMachine::render() const {
	if (!gameStates.empty()) {
		gameStates.top()->render();
	}
}
void GameStateMachine::handleEvent(const SDL_Event& event) {
	if (!gameStates.empty()) {
		
		std::shared_ptr<GameState> currentState = gameStates.top();
		currentState->handleEvent(event);
	}
}
