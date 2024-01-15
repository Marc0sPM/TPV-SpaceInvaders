#pragma once
#include <stack>
#include "GameState.h"
class GameStateMachine
{
private:
	
	std::stack<std::shared_ptr<GameState>> gameStates;
public:
	GameStateMachine();
	void pushState(std::shared_ptr<GameState> pState);
	void popState();
	void replaceState(std::shared_ptr<GameState> pState);
	void update();
	void render() const;
	void handleEvent(const SDL_Event& event);
};

