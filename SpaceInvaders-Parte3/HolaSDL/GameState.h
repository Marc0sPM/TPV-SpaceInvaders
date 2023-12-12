#pragma once
#include "gameList.h"
#include "GameObject.h"
#include <list>
#include "EventHandler.h"
#include <SDL.h>
#include <istream>
using namespace std;
class Game;
class GameState
{
private:
	Game* game;
	GameList<GameObject, true> gameList;
	list<EventHandler*> eventHandles;
public:
	GameState();
	GameState(Game* _game);
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual void save(ostream&) = 0; 
	virtual void handleEvent(const SDL_Event& event) = 0;
	void addEventListener(EventHandler* listener);
	void addObject(GameObject* gameObject);
	Game* getGame() const { return game; }
};
