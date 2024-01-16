#pragma once
#include "GameObject.h"

#include "gameList.h"
#include "texture.h"
#include <SDL.h>
#include "Vector2D.h"
#include <list>
class PlayState;
class SceneObject: public GameObject
{
protected:
	Point2D<int> pos;
	int width, height, lifes = 1;
	PlayState* playState;
	GameList<SceneObject>::anchor sceneAnchor;
public:
	SceneObject(PlayState* playState, std::istream& entrada);
	//Para los laseres
	SceneObject(PlayState* playState, Point2D<int>& pos, int width, int height);
	virtual ~SceneObject();
	void setListAnchor(GameList<SceneObject>::anchor anchor);
	virtual bool hit(SDL_Rect* attackRect, char laserType); 
	virtual void update() override;
	virtual void render()const override;
	virtual void save(std::ostream& os)const override;
	void setTexture(Texture* texture);
	GameList<SceneObject>::anchor getAnchor() { return sceneAnchor; }
	
};

