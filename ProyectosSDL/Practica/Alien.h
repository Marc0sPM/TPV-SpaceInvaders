#pragma once
#include "Vector2D.h"
#include "texture.h"
class Game {};
class Alien
{
private:
	Point2D<int> pos;
	int subtipo;
	Texture* textura;
	Game* game;
	
public:
	Alien();
	Alien(Point2D<int> _pos, int _lifes, Texture* _textura, int _subtipo, Game* _game);

	void render() const;
	bool update();
	void hit();
};

