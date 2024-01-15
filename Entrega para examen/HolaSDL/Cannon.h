#pragma once
#include "SceneObject.h"
#include "EventHandler.h"
#include "Vector2D.h"
#include "texture.h"
#include <iostream>
class Game;
class PlayState;

const int CANNON_SPEED = 3;
class Cannon : public SceneObject, public EventHandler
{
private:
	Texture* texture = nullptr;
	Point2D<int> currentMovement;
	int remainingTime;
	bool isShoot = false;
	bool hasShield = false;
	std::unique_ptr<SDL_Rect> rect; 
public:
	Cannon(PlayState* playState, std::istream& entrada, Texture* texture);
	int getTime() const;
	void setTime(int newTime);
	void render() const override;
	void update() override;
	void save(std::ostream& os) const override;
	bool hit(SDL_Rect* attackRect, char laserType) override;
	void handleEvent(const SDL_Event& event)override ;

	void setShield();

	int getLifes() { return lifes; }
	Point2D<int> getPos() { return pos; }
	SDL_Rect* getRect() const { return rect.get(); }
	Texture* getTexture() const { return texture; }

};

