
#include "Game.h"




using namespace std;
Game::Game() : window(nullptr), renderer(nullptr), exit(false), lastFrameTime(SDL_GetTicks()), alienDirection(Vector2D<int>(1, 0)), cantMove(false), TEXTURAS{
		{"aliens.png", 3, 2},
		{"bunker.png", 1, 4},
		{"spaceship.png", 1, 1},
		{"stars.png", 1, 1}
} {

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
		SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		cerr << "Error al cargar renderer: " << SDL_Error;
		return;
	}

	//Carga texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		texturas[i] = new Texture(renderer,  (TEXTURE_ROOT + TEXTURAS[i].direccion).c_str(), TEXTURAS[i].rows, TEXTURAS[i].cols);
	}

	//inicialización por lectura
	ifstream entrada;
	entrada.open("../mapas/original.txt");
	if (!entrada.is_open()) cout << "ERROR: entrada no encontrada.";
	else {
		int tipo, posX, posY;
		//inicialización de vectores de aliens y bunkers

		while (!entrada.eof()) {
			//lectura de variables
			entrada >> tipo;

			if (tipo == 0) {
				//Inicializacion canñon
				entrada >> posX;
				entrada >> posY;
				Point2D<int> posC = { posX, posY };
				myCannon = new Cannon(posC, texturas[cannon], this);
			}
			else if (tipo == 1) {
				entrada >> posX;
				entrada >> posY;
				int subtipo;
				entrada >> subtipo;
				Point2D<int> pos = { posX, posY };
				aliens.push_back(new Alien(pos, texturas[alien], subtipo, this));

			}
			else if (tipo == 2) {
				entrada >> posX;
				entrada >> posY;
				Point2D<int> pos = { posX, posY };
				bunkers.push_back(new Bunker(pos, 8, texturas[bunker]));

			}
		}
	}
	Point2D<int> aux ( 300, 400 );
	laserPrueba = new Laser(aux, false, renderer);
}
Game :: ~Game() {
	//Liberar memoria alien y bunker
	for (int i = 0; i < NUM_TEXTURES; i++) {
		delete texturas[i];
		texturas[i] = nullptr;
	}
	//Borrar aliens
	
	//Borrar bunkers
	//Borrar laseres
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Game::run() {

	while (!exit) {
		//Establecemos juego a 60 FPS
		Uint32 currentFrameTime = SDL_GetTicks();
		Uint32 frameTime = currentFrameTime - lastFrameTime;

		if (frameTime < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
		
		lastFrameTime = currentFrameTime;

		handleEvents();
		update();
		render();
	}
}
void Game::render() {

	SDL_RenderClear(renderer);
	//Render aliens
	texturas[background]->render();
	for (int i = 0; i < aliens.size(); i++) {
		aliens[i]->render();
	}
	//Render bunkers
	for (int i = 0; i < bunkers.size(); i++) {
		bunkers[i]->render();
	}
	//Render cañon
	myCannon->render();
	laserPrueba->render();
	SDL_RenderPresent(renderer);
}
void Game::update() {

	for (int i = 0; i < aliens.size(); i++) {
		aliens[i]->update();
	}
	myCannon->update();
	laserPrueba->update();
	if (cantMove) {
		alienDirection = alienDirection * -1;
		cantMove = false;
	}
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

// Calcula y devuelve la dirección común de movimiento de los Aliens
Vector2D<int> Game::getDirection() const {

	return alienDirection;

}
//Si uno de los aliens choca con los laterales de la pantalla habilita cambio direccion
void Game::cannotMove() {
	cantMove = true;
}


void Game::fireLaser() {

}