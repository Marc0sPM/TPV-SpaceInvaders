#pragma once
#include <stack>
#include "GameState.h"
class GameStateMachine
{
private:
	
	std::stack<GameState*> gameStates;

	//Acumulador de estados por borrar para que no haya fallo de acceso a memoria
	std::list<GameState*> statesToDelete;
public:
	GameStateMachine();
	~GameStateMachine();
	void pushState(GameState* state);
	void popState();
	void replaceState(GameState* state);
	void update();
	void render() const;
	void handleEvent(const SDL_Event& event);
	void clear();
};

