#pragma once

//#include <random>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include <string>
#include "checkML.h"
#include <list>
#include<random>

#include "Alien.h"
#include "Bunker.h"
#include "Texture.h"
#include "Vector2D.h"
#include "SceneObject.h"
#include "Cannon.h"
#include "Laser.h"
#include "ShooterAlien.h"
#include "Ufo.h"
#include "InfoBar.h"


constexpr Uint32 windowWidth = 800;
constexpr Uint32 windowHeight = 600;
const int NUM_TEXTURES = 6;
const int FRAME_DELAY = 16; // 60 FPS (1000 ms / 60)
const string TEXTURE_ROOT = "../images/";
const Uint32 SHOOT_ALIEN_INTERVAL = 800; // unit -> ms

class Game {
private:
	bool save, load;
	int saveNum;

	default_random_engine randomGenerator;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 deltaTime;
	bool exit;
	bool cantMove;
	int cantAliens = 0;
	int cannonY;
	
	
	int numShootAliens;
	Uint32 lastFrameTime;
	Vector2D<int> alienDirection;
	Texture* texturas[NUM_TEXTURES];

	//Lista de objetos
	list<SceneObject*> sceneObjects;
	Mothership* mothership;
	Cannon* _cannon;
	InfoBar* infoBar;

	enum textureNames {
		alien,
		bunker,
		cannon,
		background,
		ufo,
		numbers
	};
	struct TextureSpec {
		const char* direccion;
		size_t rows;
		size_t cols;
	};
	
	const TextureSpec TEXTURAS[NUM_TEXTURES];
	void readGame(string file);
	void readAliens(istream& entrada, int posX, int posY);
	void readBunkers(istream& entrada, int posX, int posY);
	void readShooterAliens(istream& entrada, int posX, int posY);
	void readCannon(istream& entrada, int posX, int posY);
	void readUfo(istream& entrada, int posX, int posY);
	void readInfoBar(istream& entrada);
	void readLasers(istream& entrada, int posX, int posY);
	void initializeSDL();
	void loadTextures();
	void saveGame(ofstream& os, bool& wait, int& saveNum);
	void loadGame(int& saveNum, bool& wait);
	
public:

	Game();
	~Game();

	void run();
	void render()const;
	void update();
	void handleEvents();
	
	int getRandomRange(int min, int max) ;

	SDL_Renderer* getRenderer() const { return renderer; }
	void increaseScore(SceneObject* object);
	bool damage(SDL_Rect* laserRect, char& src);
	void fireLaser(Point2D<int>& pos, char source);
	void hasDied(std::list<SceneObject*>::iterator& iterator);
	int getCannonPos() { return _cannon->getPos().getY(); }

};
