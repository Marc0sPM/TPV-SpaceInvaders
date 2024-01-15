#pragma once
#include "SceneObject.h"
#include "Vector2D.h"
#include "texture.h"
#include <iostream>
class Game;
class Mothership;
class PlayState;

/// Puntuaciones de los distintos aliens
const int RED_POINTS = 10;
const int GREEN_POINTS = 20;
const int SHOOTER_POINTS = 30;

class Alien: public SceneObject
{
protected:
	Texture* textura;
private:
	int indice;
	std::unique_ptr<SDL_Rect> destRect;
	Mothership* mothership;
	int animationTime;
	int currentAnimationFrame = 0;
	void playAnimation();
public:
	Alien(PlayState* playState ,std::istream& entrada,Texture* textura, Mothership* mothership);
	
	void render() const override;
	void update() override;
	void save(std::ostream& os) const override;
	void Down();
	SDL_Rect* getRect() const;
	int GetIndice() const {
		return indice;
	}
	bool hit(SDL_Rect* attackRect, char laserType) override;
	Point2D<int> getPosition() const { return pos; }
};

