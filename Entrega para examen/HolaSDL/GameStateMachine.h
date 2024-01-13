#pragma once
#include "GameState.h"
#include <stack>
#include "SDL.h"
class GameStateMachine
{
private:
	bool shouldReplace = false;
	std::stack<GameState*> gameStates;
	GameState* stateToPush;
public:
	GameStateMachine();
	//Añade estado a la pila
	void pushState(GameState* pState);
	//Elimina estado a la pila
	void popState();
	//Remplaza un estado por el actual
	void replaceState(GameState* pState);
	void update();
	void render() const;
	void handleEvent(const SDL_Event& event);
	void replace()
};

