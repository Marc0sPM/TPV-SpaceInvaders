#include "checkML.h"
#include "Reward.h"
#include "PlayState.h"
#include "Game.h"

Reward::Reward(PlayState* playState, Texture* _texture, Point2D<int>& pos) 
	: 
	SceneObject(playState, pos, _texture->getFrameWidth(), _texture->getFrameHeight()),
	texture(_texture),
	rect(std::make_unique<SDL_Rect>(SDL_Rect{ pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() }))
{
	renderer = game->getRenderer();
}
void Reward::update() {
	pos += REWARD_SPEED;
	if (playState->mayGrantReward(rect.get())) {
		lifes--;
		rewardFunction();
	}
	SceneObject::update();
}

void Reward::render()const {
	*rect = { pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() }; 
	texture->render(*rect);
}
void Reward::setFunction(Callback callback) {
	rewardFunction = callback;
}
bool Reward::hit(SDL_Rect* attackRect, char laserType) {
	return false;
}
