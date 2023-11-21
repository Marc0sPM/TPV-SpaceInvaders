#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "checkML.h"

const int ALIEN_SPEED = 10; //Pixeles de movimiento
const Uint32 MOVE_INTERVAL = 800;
class Game;
class Alien
{
private:
	Point2D<int> pos;
	int subtipo;
	Texture* textura;
	Game* game;
	int currentFrame;
	bool alive;
	SDL_Rect* rect ;
	Uint32 moveCounter;
	
	
public:
	Alien();
	Alien(Point2D<int>& _pos, Texture* _textura, int _subtipo, Game* _game);
	Point2D<int> getPos () const;
	void render() ;
	bool update();
	void hit();
	SDL_Rect* getRect() const { return rect; }
};

