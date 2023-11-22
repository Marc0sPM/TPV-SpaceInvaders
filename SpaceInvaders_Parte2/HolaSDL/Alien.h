#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "checkML.h"
#include "SceneObject.h"

const int ALIEN_SPEED = 10; //Pixeles de movimiento
const Uint32 MOVE_INTERVAL = 800;
class Game;
class Alien : public SceneObject
{
private:
	int subtipo;
	int currentFrame;
	SDL_Rect rect;
	Uint32 moveCounter;
protected:
	Texture* textura;
public:

	Alien(Game* _game, Point2D<int>& _pos, Texture* _textura, int _subtipo);
	Point2D<int> getPos () const;
	void render() ;
	bool update(Uint32 deltaTime);
	void hit(SDL_Rect attackRect, bool src) override;
	SDL_Rect getRect() const { return rect; }
};

