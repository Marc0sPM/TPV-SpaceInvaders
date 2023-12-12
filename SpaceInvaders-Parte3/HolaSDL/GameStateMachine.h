#pragma once
#include <stack>
#include "GameState.h"
class GameStateMachine
{
private:
	stack<GameState*> stack;

public:
	void pushState(GameState* gameState);
	void popState();
	void replaceState(GameState* gameState);
	void update();
	void render() const;
	void handleEvent(const SDL_Event& event);
};

