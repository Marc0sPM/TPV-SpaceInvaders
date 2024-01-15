#include "checkML.h"
#include "Game.h"
#include "Exceptions.h"



 

Game::Game() :  window(nullptr), renderer(nullptr), stateMachine(nullptr){
	lastFrameTime = SDL_GetTicks();
	initSDL();
	loadTextures();
	stateMachine = new GameStateMachine();
}
Game::~Game() {
	for (auto& it : textures) {
		delete it;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
}
void Game::initSDL() {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("SpaceInvaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	font = TTF_OpenFont(FONT_ROOT.c_str(), 24);

	//Prevencion ante fallos al cargar SDL
	if (window == nullptr) throw SDLError("Fallo al cargar la ventana");
	if (renderer == nullptr) throw SDLError("Fallo al cargar el renderer");
	if(font == nullptr) throw SDLError("Error al cargar la fuente");
}
void Game::loadTextures() {
	for (int i = 0; i < NUM_TEXTURES; ++i) {

		textures[i] = new Texture(renderer, (TEXTURE_ROOT + TEXTURES[i].filename).c_str(), TEXTURES[i].numRows, TEXTURES[i].numCols);
	}
}
void Game::run()
{
	stateMachine->pushState(std::make_shared<MainMenuState>(this));

	while (!exit) {
		Uint32 currentFrameTime = SDL_GetTicks();
		Uint32 frameTime = currentFrameTime - lastFrameTime;

		if (frameTime < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
		lastFrameTime = currentFrameTime;
		handleEvent();
		render();
		update();
	}
	
}
void Game::handleEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT)  exit = true;
		stateMachine->handleEvent(event);
	}
}
void Game:: update() {
	stateMachine->update();
}
void Game::render() const {
	SDL_RenderClear(renderer);

	stateMachine->render();

	SDL_RenderPresent(renderer);
}

void Game::exitGame() {
		exit = true;
}
