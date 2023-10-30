
#include "Game.h"

using namespace std;
Game::Game() : window(nullptr), renderer(nullptr), exit(false){
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
	texturas[Alien] = new Texture(renderer, "images/aliens.png", 3, 2);
	texturas[Bunker] = new Texture(renderer, "images/bunker.png", 1, 4);
	texturas[Cannon] = new Texture(renderer, "images/cannon.png", 1, 1);
	/*texturas[LaserTexture] = Texture(renderer, "images/laser.png", 1, 1);
	* Preguntar como se crea el laser ....*/
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
Vector2D<int> Game::getDirection() {
	// Calcula y devuelve la dirección común de movimiento de los Aliens
	return Vector2D<int>(1, 0); // Ejemplo de dirección a la derecha
}