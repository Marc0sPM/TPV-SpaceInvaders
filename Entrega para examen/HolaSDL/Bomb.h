#pragma once
#include "Texture.h"
#include "SceneObject.h"
#include "GameObject.h"
#include <iostream>

class Game;
class PlayState;
const int BOMB_LIFES = 2;
const Point2D<int> BOMB_SPEED{ 0,1 };
class Bomb : public SceneObject
{
private:
	Texture* texture;
	std::unique_ptr<SDL_Rect> rect;
	
public:
	Bomb(PlayState* playState, Texture* _texture, std::istream& entrada);
	Bomb(PlayState* playState, Texture* texture, Point2D<int> pos);
	void render() const override;
	void update() override;
	void save(std::ostream& os) const override;
	bool hit(SDL_Rect* attackRect, char laserType) override;
};

