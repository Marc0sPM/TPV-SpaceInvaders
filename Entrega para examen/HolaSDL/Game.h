#pragma once
#include "GameStateMachine.h"
#include "MainMenuState.h"

#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include <string>
#include <SDL_ttf.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int NUM_TEXTURES = 20;
const int FRAME_DELAY = 16; // 60 FPS 
const std::string TEXTURE_ROOT = "../images/";
const std::string FONT_ROOT = "../images/PressStart2P-Regular.ttf";

struct TextureSpec {
	const char* filename;
	size_t numRows;
	size_t numCols;
};

const enum TextureName {
	ALIEN,
	BUNKER,
	CANNON,
	BACKGROUND,
	UFO,
	INFOBAR,
	NEW_GAME,
	LOAD_GAME,
	EXIT,
	SAVE_GAME,
	RETURN,
	CONTINUE,
	GAMEOVER,
	WIN,
	CODIGO,
	BOMB,
	SHIELD_REWARD,
	SHIELD,
	MAIN_MENU,
	BOX
};
const TextureSpec TEXTURES[] = {
		{"aliens.png", 3, 2},
		{"bunker.png", 1, 4},
		{"spaceship.png", 1, 1},
		{"stars.png", 1, 1},
		{"ufo.png",1,2},
		{"numbers.png",1,10},
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
		{"boxtext.png", 1,1}
};

class Game
{
private:
	bool exit = false;
	Uint32 lastFrameTime;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	
	GameStateMachine* stateMachine;

	Texture* textures[NUM_TEXTURES];
	void initSDL();
	void loadTextures();
	
public:
	Game();
	~Game();
	void run();
	void handleEvent();
	void update();
	void render() const;
	
	void exitGame();
	
	Texture* getTexture(TextureName name) { return textures[name]; }
	GameStateMachine* getGameStateMachine() { return stateMachine; }
	SDL_Renderer* getRenderer() { return renderer; }
	SDL_Window* getWindow() { return window; }
	TTF_Font* getFont() { return font; }
	//// Métodos para manejar guardado y carga de partidas
	//void saveGame(const std::string& filename);
	//void loadGame(const std::string& filename);
};

