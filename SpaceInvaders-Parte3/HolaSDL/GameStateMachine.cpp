#include "GameStateMachine.h"
void GameStateMachine::pushState(GameState* gameState){
	stack.push(gameState);
}
void GameStateMachine::popState() {
	if (!stack.empty()){
		delete stack.top();
		stack.pop();
	}
}
void GameStateMachine::replaceState(GameState* gameState) {
	if (!stack.empty()) {
		delete stack.top();
		stack.pop();
	}
	stack.push(gameState);
}
void GameStateMachine::render() const {
	if (!stack.empty()) {
		stack.top()->render();
	}
}
void GameStateMachine::update() {
	if (!stack.empty()) {
		stack.top()->update();
	}
}
void GameStateMachine::handleEvent(const SDL_Event& event) {
	if (!stack.empty()) {
		stack.top()->handleEvent(event);
	}
}