
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

	
	
	//inicializaci�n por lectura
	
		ifstream entrada;
		entrada.open("../mapas/original.txt");
		if (!entrada.is_open()) cout << "ERROR: entrada no encontrada.";
		else {
			int tipo, posX, posY;
			//inicializaci�n de vectores de aliens y bunkers
			aliens = new vector<Alien>;
			bunkers = new vector<Bunker>;
			while (!entrada.eof()) {
				//lectura de variables
				entrada >> tipo;
					
				if (tipo == 0) {
					//Inicializacion can�on
					entrada >> posX;
					entrada >> posY;
					Point2D<int> posC = { posX, posY };
					myCannon = new Cannon(posC, texturas[cannon], this);
				}
				else if(tipo == 1){
					entrada >> posX;
					entrada >> posY;
					int subtipo;
					entrada >> subtipo;
					Point2D<int> pos = { posX, posY };
					aliens->push_back(Alien(pos, texturas[alien], subtipo, this));
						
				}
				else if (tipo == 2) {
					entrada >> posX;
					entrada >> posY;
					Point2D<int> pos = {posX, posY };
					bunkers->push_back(Bunker(pos, 8, texturas[bunker]));
					
				}
					
					

			}
				
				
		}
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
	//Render ca�on
	myCannon->render();
	SDL_RenderPresent(renderer); 
}
void Game::update() {
	for (int i = 0; i < aliens->size(); i++) {
		(*aliens)[i].update();
	}
	myCannon->update();
}
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		myCannon->handleEvents(event);
	}
}
Vector2D<int> Game::getDirection() {
	// Calcula y devuelve la direcci�n com�n de movimiento de los Aliens
	return { 0,0 };
	
}
bool Game::cannotMove() {
	return false;
}

void Game::fireLaser() {

}