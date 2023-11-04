#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Alien.h"
#include "Bunker.h"
#include "Texture.h"
#include "Vector2D.h"
#include "Cannon.h"
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




class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool exit;
	bool cantMove;
	vector<Alien*> aliens; //no array dinamico
	vector<Bunker*> bunkers; 
	Cannon* myCannon;
	//Añadir laseres--------------/
	
	Uint32 lastFrameTime;
	Vector2D<int> alienDirection;
	Texture* texturas[NUM_TEXTURES];
	

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
	void update();
	void handleEvents();
	Vector2D<int> getDirection()const; 
	void cannotMove() ;
	
	void fireLaser();
};
