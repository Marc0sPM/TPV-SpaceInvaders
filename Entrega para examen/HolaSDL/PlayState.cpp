#include "PlayState.h"
#include "Game.h"

PlayState::PlayState(Game* game, std::string in) 
	: 
	GameState(game), 
	in(in) 
{
	mothership = new Mothership(game);
	addObject(mothership);
	readGame(in);
}
void PlayState::update() {
	if(mothership->getCont() <= 0) { /*lanzar estado de EndState -> true*/ }
	if(mothership->haveLanded() || cannon->getLifes()<= 0) {/*Lanzar estado de EndState -> false*/ }
	for (auto& anchor : gameObjects) {
		anchor.update();
	}
	for (auto& anchor : sceneObjects) {
		anchor.update();
	}
}

void PlayState::render()const {
	game->getTexture
}