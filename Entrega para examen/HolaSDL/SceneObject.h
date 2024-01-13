#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>
#include "gameList.h"
#include "texture.h"
#include "checkML.h"

class PlayState;
class SceneObject : public GameObject
{
protected:
	Point2D<int> pos;
	int lifes = 1, width, height;
	GameList<SceneObject>::anchor sceneAnchor;
	PlayState* playState;
public:
	//Constructora por lectura desde entrada
	SceneObject(PlayState* playState, std::istream& in);
	//Constructora por instancia de objecto en escena
	SceneObject(PlayState* playState, Point2D<int> pos, int width, int height);
	void setSceneAnchor(GameList<SceneObject>::anchor anchor);
	virtual bool hit(SDL_Rect* attackRect, char laserSrc);
	virtual void update() override;

};

