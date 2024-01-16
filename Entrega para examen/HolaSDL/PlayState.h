#pragma once
#include "GameState.h"
#include "gameList.h"
#include "Exceptions.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include <list>
#include<random>

#include "Bomb.h"
#include "Alien.h"
#include "Bunker.h"
#include "Texture.h"
#include "Vector2D.h"
#include "SceneObject.h"
#include "Reward.h"
#include "Laser.h"
#include "ShooterAlien.h"
#include "Ufo.h"
#include "InfoBar.h"

class PauseState;
class PlayState: public GameState
{
private:
	GameList<SceneObject,false> sceneObjects;
	default_random_engine randomGenerator;
	Cannon* cannon;
	Mothership* mothership;
	InfoBar* infoBar;
	std::string entrada;

	//Funciones de lectura e inicializacion
	void readGame(string file);
	void destroyAllObjects();
	void setToList(SceneObject* object);
	void initBomb(Point2D<int>& pos);
	void initShield(Point2D<int>& pos);
public:
	PlayState(Game* game, std::string entrada);
	~PlayState();

	void update() override;		
	void render() const override;
	void hasDied(GameList<GameObject, true>::anchor an) override;
	void hasDied(GameList<SceneObject>::anchor an );
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream& os) const override;
	int getCannonPosY(){ return cannon->getPos().getY(); }
	bool damage(SDL_Rect* rect, char layerType);
	int getRandomRange(int min, int max);
	void fireLaser(Point2D<int>& pos, char source);
	void increasePunctuation(int points);
	void GenerateUFOObject(Point2D<int>& pos);
	bool mayGrantReward(SDL_Rect* rewardRect);
	void setShield();
	void saveGame(std::string file);
	void loadGame(std::string filename);
};

