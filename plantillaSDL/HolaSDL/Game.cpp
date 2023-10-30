
#include "Game.h"

using namespace std;
Game::Game() : window(nullptr), renderer(nullptr), exit(false), aliens(nullptr), bunkers(nullptr) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cerr << "Error al inicializar SDL: " << SDL_Error;
		return;
	}

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cerr << "Error al cargar ventana: " << SDL_Error;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		cerr << "Error al cargar renderer: " << SDL_Error;
		return;
	}
	//Carga texturas
	texturas[alien] = new Texture(renderer, "../images/aliens.png", 3, 2);
	texturas[bunker] = new Texture(renderer, "../images/bunker.png", 1, 4);
	texturas[cannon] = new Texture(renderer, "../images/spaceship.png", 1, 1);
	texturas[background] = new Texture(renderer, "../images/stars.png", 1, 1);

	//Inicialización aliens
	aliens = new vector<Alien>;
	Vector2D<int>pos = { 50,0 };
	Vector2D<int>posGlob = { 0,0 };
	for (int i = 0; i < 6; i++) {
		posGlob = posGlob + pos;
		aliens->push_back(Alien(posGlob, texturas[alien], 2, this));
	}
	//Inicializacion bunkers
	bunkers = new vector<Bunker>;
	Vector2D<int> pos1 = { 150 ,0 };
	Vector2D<int> posG = { 0, 400 };
	for (int i = 0; i < 4; i++) {
		posG = pos1 + posG;
		bunkers->push_back(Bunker(posG, 8, texturas[bunker]));
	}
	//Inicializacion canñon
	Point2D<int> posC = { 400, 500 };
	myCannon = new Cannon(posC, texturas[cannon], this);
}
Game :: ~Game() {
	//Liberar memoria alien y bunker
	for (int i = 0; i < NUM_TEXTURES; i++) {
		delete texturas[i];
		texturas[i] = nullptr;
	}

	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(window);
	SDL_Quit(); 
}
void Game::run() {
	while (!exit) {
		handleEvents(); 
		update(); 
		render(); 
	}
}
void Game::render() {
	SDL_RenderClear(renderer);
	//Render aliens
	for (int i = 0; i < aliens->size(); i++) {
		(*aliens)[i].render();
	}
	//Render bunkers
	for (int i = 0; i < bunkers->size(); i++) {
		(*bunkers)[i].render();
	}
	SDL_RenderPresent(renderer);
}
void Game::update() {

}
void Game::handleEvents() {

}
//Vector2D<int> Game::getDirection() {
//	// Calcula y devuelve la dirección común de movimiento de los Aliens
//	
//}
//bool Game::cannotMove() {
//
//}

void Game::fireLaser() {

}