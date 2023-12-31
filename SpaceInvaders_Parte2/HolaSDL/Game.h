#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Alien.h"
#include "Bunker.h"
#include "Texture.h"
#include "Vector2D.h"
#include "SceneObject.h"
#include "Cannon.h"
#include "Laser.h"
#include "ShooterAlien.h"
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <cstring>
#include "checkML.h"
#include <list>

using namespace std;

constexpr Uint32 windowWidth = 800;
constexpr Uint32 windowHeight = 600;
const int NUM_TEXTURES = 4;
const int FRAME_DELAY = 16; // 60 FPS (1000 ms / 60)
const string TEXTURE_ROOT = "../images/";
const Uint32 SHOOT_ALIEN_INTERVAL = 800; // unit -> ms




class Game {
private:
	default_random_engine rendomGenerator;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 deltaTime;
	bool exit;
	bool cantMove;
	
	//HAY QUE QUITAR LOS VECTORES
	vector<Alien*> aliens; //no array dinamico
	vector<Bunker*> bunkers; 
	vector<Laser*> lasers;
	Cannon* myCannon;
	//HASTA AQUI
	
	int numShootAliens;
	Uint32 lastFrameTime;
	Vector2D<int> alienDirection;
	Texture* texturas[NUM_TEXTURES];
	
	//Lista de objetos
	list<SceneObject*> sceneObjects;

	enum textureNames{
		alien,
		bunker,
		cannon,
		background
	};
	struct TextureSpec {
		const char* direccion;
		size_t rows;
		size_t cols;
	};
	
	const TextureSpec TEXTURAS[NUM_TEXTURES];
	void readGame();
	void readAliens(istream& entrada, int posX, int posY); 
	void readBunkers(istream& entrada, int posX, int posY);
	void readShooterAliens(istream& entrada, int posX, int posY);
	void readCannon(istream& entrada, int posX, int posY);
	void initializeSDL();
	void loadTextures();
public:
	
	Game();
	~Game();

	void run();
	void render();
	void update(const Uint32 deltTime);
	void handleEvents();

	Vector2D<int> getDirection()const; 
	void cannotMove() ;
	int getRandomRange(int min, int max) const;
	
	bool bunkerColision(SDL_Rect* laserRect);
	bool laserColision(SDL_Rect* laserRect, bool laserSrc);
	bool alienColision(SDL_Rect* laserRect);
	bool cannonColision(SDL_Rect* laserRect);
	SDL_Renderer* getRenderer() const { return renderer; }
	
	void fireLaser(Point2D<int>& pos, bool source);
	void hasDied(std::list<SceneObject*>::iterator iterator);
	
};
