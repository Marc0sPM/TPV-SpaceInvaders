#pragma once
#include "Vector2D.h"
#include "texture.h"

const int ALIEN_SPEED = 2; //Pixeles de movimiento

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
	
public:
	Alien();
	Alien(Point2D<int>& _pos, Texture* _textura, int _subtipo, Game* _game);
	Point2D<int> getPos () const;
	void render() const;
	bool update();
	void hit();
	Texture* getTexture() const;
	Point2D<int> getPos();
};

