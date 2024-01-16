#pragma once
//#include <SDL.h>
#include "gameList.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "Exceptions.h"
#include <ostream>
#include <list>
#include <string>

constexpr int MESSAGE_WINDOW_WIDTH = 200;
constexpr int MESSAGE_WINDOW_HEIGHT = 150;
const std::string NEWGAME_ROOT = "../mapas/default/original.txt";
const std::string LOADGAME_ROOT = "../mapas/save/";

class Game;
class GameState
{
protected:
	Game* game;
	GameList<GameObject, true> gameObjects;
	std::list<EventHandler*> eventHandlers;
public:
	
	GameState(Game* game);
	virtual ~GameState(){}
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvent(const SDL_Event& event) = 0;
	virtual void save(std::ostream&) const = 0;
	virtual void hasDied(GameList<GameObject, true>::anchor) = 0;
	Game* getGame() const {
		return game;
	}
	void addEventListener(EventHandler* listener);
	void addObject(GameObject* object);
	SDL_Window* createMessageWindow();
};

