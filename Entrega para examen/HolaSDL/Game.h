#pragma once

#include "GameStateMachine.h"
#include "MainMenuState.h"

#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"


constexpr Uint32 WINDOW_WIDTH = 800;
constexpr Uint32 WINDOW_HEIGHT = 600;
constexpr int NUM_TEXTURES = 20;
const int FRAME_DELAY = 16; // 60 FPS 
const std::string TEXTURE_ROOT = "../images/";
struct TextureSpec {
	const char* direccion;
	size_t rows;
	size_t cols;
};
const enum TextureNames {
	ALIEN,
	BUNKER,
	CANNON,
	BACKGORUND,
	UFO,
	INFOBAR,
	NEW_GAME,
	LOAD_GAME,
	EXIT,
	SAVE_GAME,
	CONTINUE,
	RETURN,
	GAME_OVER,
	WIN,
	CODE,
	BOMB,
	SHIELD_REWARD,
	SHIELD,
	MAIN_MENU,
	BOX_TEXT
};
const TextureSpec TEXTURES [] = {
	{"aliens.png", 3, 2},
	{"bunker.png", 1, 4},
	{"spaceship.png", 1, 1},
	{"stars.png", 1, 1},
	{"ufo.png", 1, 2},
	{"numbers.png", 1, 10},
	{"nuevaPartida.png", 1,1},
	{"cargarPartida.png", 1,1},
	{"salir.png", 1,1},
	{"guardarPartida.png", 1,1},
	{"volverAlMenu.png", 1,1},
	{"continuar.png", 1,1},
	{"gameOver.png", 1,1},
	{"hasGanado.png", 1,1},
	{"codigo.png", 1,1},
	{"bomb.png", 1,1},
	{"shield_reward.png", 1,1},
	{"shield.png", 1,1},
	{"mainMenu.png", 1,1},
	{"boxtext.png", 1,1} };

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 lastFrameTime;
	bool exit = false;
	
	Texture* textures[NUM_TEXTURES];
	GameStateMachine* stateMachine;

	void intitSDL();
	void loadTextures();
	
public:

	Game();
	~Game();
	void run();
	void handleEvent();
	void update();
	void render() const;

	Texture* getTexture(TextureNames name) {
		return textures[name];
	}

	GameStateMachine* getGameStateMachine() {
		return stateMachine;
	}

	SDL_Renderer* getRenderer() { return renderer; }
	SDL_Window* getWindow() { return window; }
	void exitGame();

};
