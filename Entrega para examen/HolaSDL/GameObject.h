#pragma once
#include <ostream>
#include "gameList.h"

class Game;
class GameObject
{
protected:
	Game* game;
	GameList<GameObject, true>::anchor listAnchor;
public:
	GameObject(Game* game);
	virtual ~GameObject();
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void save(std::ostream& os) const = 0;
	void setListAnchor(GameList<GameObject, true>::anchor objAnchor);
};

