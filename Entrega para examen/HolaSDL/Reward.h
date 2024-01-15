#pragma once
#include "Vector2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include <functional>
#include "SceneObject.h"

const Point2D<int> REWARD_SPEED = { 0, 1 };
class Game;
class PlayState;
class Reward : public SceneObject
{
public:
	using Callback = std::function<void(void)>;
private:
	Texture* texture;
	Callback rewardFunction;
	SDL_Renderer* renderer;
	std::unique_ptr<SDL_Rect> rect;
	
public:
	Reward(PlayState* playState, Texture* _texture, Point2D<int>& _pos);

	void update() override;
	void render()const override;
	void setFunction(Callback callback);
	bool hit(SDL_Rect* attackRect, char laserType) override;


};

