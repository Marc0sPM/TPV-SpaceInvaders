#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Alien.h"
#include "Bunker.h"
#include "Texture.h"
#include "Vector2D.h"
#include "Cannon.h"
#include "Laser.h"
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

constexpr Uint32 windowWidth = 800;
constexpr Uint32 windowHeight = 600;
const int NUM_TEXTURES = 4;
const int FRAME_DELAY = 16; // 60 FPS (1000 ms / 60)
const string TEXTURE_ROOT = "../images/";
const Uint32 SHOOT_ALIEN_INTERVAL = 800; // unit -> ms




class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 deltaTime;
	bool exit;
	bool cantMove;
	vector<Alien*> aliens; //no array dinamico
	vector<Bunker*> bunkers; 
	vector<Laser*> lasers;
	Cannon* myCannon;
	Laser* laserPrueba;
	//Añadir laseres--------------/
	int numShootAliens;
	Uint32 lastFrameTime;
	Vector2D<int> alienDirection;
	Texture* texturas[NUM_TEXTURES];

	Uint32 shootAlienCounter;
	

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
	
public:
	
	Game();
	~Game();
	void run();
	void render();
	void update(const Uint32 deltTime);
	void handleEvents();
	Vector2D<int> getDirection()const; 
	void cannotMove() ;
	int getRandomRange(int min, int max);
	vector<Bunker*> getBunkers()const;
	vector<Alien*> getAliens() const;
	void fireLaser(Point2D<int>& pos, bool source);
};
