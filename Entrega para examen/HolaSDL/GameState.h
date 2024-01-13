#pragma once
#include "GameObject.h"
#include "gameList.h"
#include "EventHandler.h"
#include <list>


class Game;
class GameState
{
protected:
	Game* game;
	GameList<GameObject, true> gameObjects;
	std::list<EventHandler*> eventHandlers;
public:
	//Constructora 
	GameState(Game* game) : game(game){}

	virtual void render()const = 0; 
	virtual void update() = 0;
	virtual void handleEvent(const SDL_Event& event) = 0;
	virtual void save(std::ostream& os) const = 0;
	virtual void hasDied(GameList<GameObject, true>::anchor an) = 0;
	Game* getGame() { return game; }
	void addEventListener(EventHandler* listener);
	void addObject(GameObject* object);
};

