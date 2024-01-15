#pragma once
#include "SceneObject.h"

#include "Vector2D.h"
#include "texture.h"
#include <iostream>
class Game;
class PlayState;
class Bunker: public SceneObject
{
private:
	Texture* texture = nullptr;
	std::unique_ptr<SDL_Rect> rect;
public:
	Bunker(PlayState* playState, std::istream& entrada, Texture* texture);
	void render() const override;
	void update() override;
	void save(std::ostream& os) const override;
	bool hit(SDL_Rect* attackRect, char laserType) override;
	SDL_Rect* getRect() const;
	
};

