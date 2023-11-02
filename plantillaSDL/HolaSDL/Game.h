#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Alien.h"
#include "Bunker.h" 
#include "texture.h"
#include "Vector2D.h"
#include "cannon.h"
#include <vector>
#include <random>
#include <fstream>

using namespace std;
constexpr Uint32 windowWidth = 800;
constexpr Uint32 windowHeight = 600;
const int NUM_TEXTURES = 4;
const int FRAME_DELAY = 16; // 60 FPS (1000 ms / 60)
class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool exit;
	vector<Alien>* aliens; //no array dinamico
	vector<Bunker>* bunkers;
	Cannon* myCannon;
	//Añadir laseres--------------/
	
	Uint32 lastFrameTime;
	Vector2D<int> alienDirection;
	Texture* texturas [NUM_TEXTURES];
	enum textureNames{
		alien,
		bunker,
		cannon,
		background
	};
public:
	
	Game();
	~Game();
	void run();
	void render();
	void update();
	void handleEvents();
	Vector2D<int> getDirection()const; 
	//void cannotMove() ;
	bool cannotMove();
	void fireLaser();
};
