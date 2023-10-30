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

class Game {
private:
	const Uint32 windowWidth = 800;
	const Uint32 windowHeight = 600;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool exit;
	vector<Alien>* aliens;
	vector<Bunker>* bunkers;
	Cannon* myCannon;
	//Añadir laseres--------------/
	//Añadir cañón----------------/
	static const int NUM_TEXTURES = 4;
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
	Vector2D<int> getDirection(); 
	bool cannotMove();
	void fireLaser();
};
