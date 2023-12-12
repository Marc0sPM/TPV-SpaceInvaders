#pragma once

#include "Vector2D.h"
#include "texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "SceneObject.h"
#include "checkML.h"
#include <istream>

const int SPEED = 2;
const Uint32 SHOOT_INTERVAL = 700; //tiempo entre cada disparo (0.8s)
class Game;
class Cannon : public SceneObject
{
protected:
	Texture* textura;
	int remainingTime;
	Vector2D<int> moveDirection = { 0,0 };
	bool isMoving = false;
	Uint32 shootCounter = 0;
	bool canShoot = true;
	SDL_Rect* rect;

public:
	Cannon(Point2D<int>& _pos, int _lives, int _remainingTime, Game* _game, Texture* _textura);
	void render() const override;
	void update() override;
	void save(std::ostream& os) const override;
	bool hit(SDL_Rect* otherRect, char otherSrc);
	void handleEvents(const SDL_Event& event);
	SDL_Rect* getRect() const { return rect; }
	Point2D<int> getPos() const { return pos; }
	int getLifes() { return lifes; }

};
