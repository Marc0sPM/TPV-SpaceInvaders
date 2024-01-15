#include "checkML.h"
#include "PlayState.h"
#include "Game.h"
#include "Mothership.h"
#include "Cannon.h"
#include "PauseState.h"
#include "EndState.h"

PlayState::PlayState(Game* game, std::string _entrada): GameState(game), entrada(_entrada){
	//Inicializar mothership
	mothership = new Mothership(game);
	addObject(mothership);
	readGame(entrada);
	pauseState = make_shared<PauseState>(game, this);
}

PlayState::~PlayState() {
	/*for (auto an : sceneObjects) {
		delete (&an);
	}*/
}

void PlayState::update() {	
	if (mothership->getCont() <= 0) {
		game->getGameStateMachine()->replaceState(std::make_shared<EndState>(game, true));
	}
	else if(mothership->haveLanded() || cannon->getLifes() <= 0)
		game->getGameStateMachine()->replaceState(std::make_shared<EndState>(game, false));
	for (auto& an : gameObjects) {
		an.update();
	}
	for (auto& an : sceneObjects) {
		an.update();
	}
	
}
	

void PlayState::render() const {
	game->getTexture(TextureName::BACKGROUND)->render();
	for (auto& an : sceneObjects) {
		an.render();
	}
	for (auto& an : gameObjects) {
		an.render();
	}
}
void PlayState::hasDied(GameList<SceneObject>::anchor an) {
	sceneObjects.erase(an);
}
void PlayState::hasDied(GameList<GameObject, true>::anchor an) {
	gameObjects.erase(an);
}
void PlayState::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	game->getGameStateMachine()->pushState(pauseState);

	for (auto& handler : eventHandlers) {
		handler->handleEvent(event);
	}
}

void PlayState::saveGame(std::string file) {
	std::ofstream os;

	os.open(file);
	if (os.is_open()) {
		for (GameList<SceneObject>::forward_iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
			(*it).save(os);
		}
		infoBar->save(os);
	}
}
bool PlayState::mayGrantReward(SDL_Rect* rewardRect) {
	return SDL_HasIntersection(rewardRect, cannon->getRect());
}
void PlayState::save(std::ostream& os ) const {
	
}

void PlayState::loadGame(std::string fileName) { 
	destroyAllObjects();
	eventHandlers.clear();
	gameObjects.clear();
	mothership = new Mothership(game);
	addObject(mothership);
	readGame(fileName);
}
void PlayState::destroyAllObjects() {
	sceneObjects.clear();

}
void PlayState::fireLaser(Point2D<int>& pos, char source) {
	Laser* l = new Laser(this, pos, source);
	sceneObjects.push_back(l);
}

void PlayState::GenerateUFOObject(Point2D<int>& pos) {
	int aux;
	aux = getRandomRange(0, 2);
	if (aux == 1) {
		initBomb(pos);
	}
	else if (aux == 2) {
		initShield(pos);
	}
}
void PlayState::initBomb(Point2D<int>& pos) {
	Bomb* bomb = new Bomb(this, game->getTexture(TextureName::BOMB), pos);
	sceneObjects.push_back(bomb);
}
void PlayState::initShield(Point2D<int>& pos) {
	Reward* shield = new Reward(this, game->getTexture(TextureName::SHIELD_REWARD), pos);
	sceneObjects.push_back(shield);
	shield->setFunction([this]() {
		setShield();
		});
}
void PlayState::setShield() {
	cannon->setShield();
}
//elimina objeto de la lista

bool PlayState::damage(SDL_Rect* laserRect, char src) {
	for (auto& obj : sceneObjects) {
		if (obj.hit(laserRect, src)) {
			return true;
		}
			
	}
	return false;
}
int PlayState::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}
void PlayState::increasePunctuation(int points) {
	infoBar->addScore(points);
}

#pragma region LECTURA DEL JUEGO 


void PlayState::readGame(string file) {
	ifstream entrada;

	entrada.open(file);

	if (!entrada.is_open()) throw FileNotFoundError("ERROR: entrada no encontrada.");
	else {
		int object;
		//inicialización de vectores de aliens y bunkers

		while (entrada >> object) {
			//lectura de variables

			//cannon
			if (object == 0) {
				cannon = new Cannon(this, entrada, game->getTexture(TextureName::CANNON));
				setToList(cannon);
				addEventListener(cannon);
			}
			//aliens
			else if (object == 1) {
				setToList(new Alien(this, entrada, game->getTexture(TextureName::ALIEN), mothership));
				mothership->addAlien();
			}
			//shooter alien
			else if (object == 2) {
				setToList(new ShooterAlien(this, entrada, game->getTexture(TextureName::ALIEN), mothership));
				mothership->addAlien();
			}
			//bunker
			else if (object == 4) setToList(new Bunker(this, entrada, game->getTexture(TextureName::BUNKER)));
			//ufo
			else if (object == 5) setToList(new Ufo(this, entrada, game->getTexture(TextureName::UFO)));
			//laser
			else if (object == 6) setToList(new Laser(this, entrada));
			else if (object == 7) {
				infoBar = new InfoBar(game, entrada, game->getTexture(TextureName::INFOBAR), game->getTexture(TextureName::CANNON), cannon);
				addObject(infoBar);
			}

		}
		entrada.close();
	}
}

void PlayState::setToList(SceneObject* object) {   
	sceneObjects.push_back(object);  
}
#pragma endregion