
#include "Game.h"


Game::Game() 
	: 
	window(nullptr), 
	renderer(nullptr), 
	lastFrameTime(SDL_GetTicks())
{
	//Inicializacion de SDL 
	initSDL(); 
	//Carga texturas 
	loadTextures(); 

	stateMachine = new GameStateMachine();
}
Game :: ~Game() {
	delete stateMachine;
	for (auto& tex : textures) {
		delete tex;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run() {

	stateMachine->pushState(new MainMenuState(this));

	while (!exit) {
		//Establecemos juego a 60 FPS
		Uint32 currentFrameTime = SDL_GetTicks();
		Uint32 deltaTime = currentFrameTime - lastFrameTime;
		if (deltaTime < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - deltaTime);
		}
		lastFrameTime = currentFrameTime;
		handleEvents();
		update();
		render();
	}
}

void Game::render() const {
	SDL_RenderClear(renderer);
	stateMachine->render();
	SDL_RenderPresent(renderer);
}

void Game::update() {
	stateMachine->update();

}
void Game::handleEvents() {
	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) exit = true;
		
		stateMachine->handleEvent(event);
		
	}
}

void Game::loadTextures() {
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		textures[i] = new Texture(renderer, (TEXTURE_ROOT + TEXTURES[i].direccion).c_str(), TEXTURES[i].rows, TEXTURES[i].cols);
	}
}
void Game::initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw SDLError("Error al inicializar SDL");
	}

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED);
	if (window == nullptr ||renderer == nullptr) {
		throw  SDLError("ERROR: Window or renderer failed");
	}
	
}

