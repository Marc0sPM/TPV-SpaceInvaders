#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(){}
void GameStateMachine::pushState(GameState* state) {
	gameStates.push(state);
}
void GameStateMachine::popState() {
	if (!gameStates.empty()) {
		delete gameStates.top();
		gameStates.pop();
	}
}
void GameStateMachine::replaceState(GameState* state) {
	stateToPush = state;
	shouldReplace = true;
}
void GameStateMachine::update() {
	if (!gameStates.empty()) {
		if (shouldReplace) replace();
		gameStates.top()->update();
	}
}
void GameStateMachine::render() const {
	if (!gameStates.empty()) gameStates.top()->render();
}
void GameStateMachine::handleEvent(const SDL_Event& event){
	if (!gameStates.empty()) gameStates.top()->handleEvent(event);
}
void GameStateMachine::replace() {
	popState();
	pushState(stateToPush);
}