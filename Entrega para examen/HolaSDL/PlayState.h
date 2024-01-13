#pragma once
#include "GameState.h"
#include "gameList.h"
#include "Alien.h"
/*--------*/
#include "Alien.h"
//#include "Bomb.h"
#include "Bunker.h"
#include "InfoBar.h"
#include "Laser.h"
//#include "Reward.h"
#include "SceneObject.h"
#include "ShooterAlien.h"
#include "Texture.h"
#include "Ufo.h"
#include "Vector2D.h"
/*--------*/
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include<random>

class Game;
class PlayState : public GameState
{
private:
	GameList<SceneObject> sceneObjects;
	default_random_engine randomGenerator;
	Cannon* cannon;
	Mothership* mothership;
	InfoBar* infoBar;
	string in;

	void readGame(string file);
	void cleanScene();
	void setToList();
	void initBomb();
	void initShield();
public: 
	PlayState(Game* game, string in);
	void update() override;
	void render() const override;
	void hasDied(GameList<GameObject, true>::anchor an) override;
	void hasDied(GameList<SceneObject>::anchor an);
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream& os) const override;
	int getCannonPosY() { return cannon->getPos().getY(); }
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

