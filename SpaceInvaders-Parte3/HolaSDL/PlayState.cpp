#include "PlayState.h"
void PlayState::update() {
	for (auto& it : sceneObjects) {
		it.update();
	}
}
void PlayState::render() const {
	for (auto& it : sceneObjects) {
		it.render();
	}
}

int PlayState::getRandomRange(int min, int max) {
	//return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}