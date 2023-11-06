
#include "Game.h"




using namespace std;
Game::Game() : window(nullptr), renderer(nullptr), exit(false), lastFrameTime(SDL_GetTicks()), alienDirection(Vector2D<int>(1, 0)), cantMove(false), numShootAliens(0),
TEXTURAS{
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
				if (subtipo == 0) numShootAliens++;
				Point2D<int> pos = { posX, posY };
				aliens.push_back(new Alien(pos, texturas[alien], subtipo, this));

			}
			else if (tipo == 2) {
				entrada >> posX;
				entrada >> posY;
				Point2D<int> pos = { posX, posY };
				bunkers.push_back(new Bunker(pos, 4, texturas[bunker]));

			}

		}
	}
	shootAlienCounter = 0;
}
Game :: ~Game() {
	//Liberar memoria alien y bunker
	for (int i = 0; i < NUM_TEXTURES; i++) {
		delete texturas[i];
		texturas[i] = nullptr;
	}
	//Borrar aliens
	for (int i = 0; i < aliens.size(); i++) {
		delete aliens[i];
		aliens[i] = nullptr;
	}
	aliens.clear();
	//Borrar bunkers
	for (int i = 0; i < bunkers.size(); i++) {
		delete bunkers[i];
		bunkers[i] = nullptr;
	}
	bunkers.clear();
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
		deltaTime = frameTime;
		if (frameTime < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
		
		lastFrameTime = currentFrameTime;

		handleEvents();
		update(deltaTime);
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
	//Render lasers
	for (int i = 0; i < lasers.size(); i++) {
		lasers[i]->render();
	}
	SDL_RenderPresent(renderer);
}
void Game::update(const Uint32 deltaTime) {
	//Contador para disparo alien
	if (shootAlienCounter < SHOOT_ALIEN_INTERVAL) {
		shootAlienCounter += deltaTime;
	}
	else {
		shootAlienCounter = 0;
		Alien* randomAlien = aliens[getRandomRange(0, numShootAliens)];
		Point2D<int> alienCenteredPos(randomAlien->getPos().getX() + (texturas[alien]->getFrameWidth() / 2), randomAlien->getPos().getY());
		fireLaser(alienCenteredPos, true);
	}
	//Update aliens
	for (int i = 0; i < aliens.size(); i++) {
		if (!aliens[i]->update()) { 
			delete aliens[i]; 
			aliens.erase(aliens.begin() + i); 
			i--; //Para que no se salte el siguiente elemento por el resize del vector
		}
		
	}
	//Update bunkers
	for (int i = 0; i < bunkers.size(); i++) {
		
		if (!bunkers[i]->update()) {
			delete bunkers[i]; 
			bunkers.erase(bunkers.begin() + i); 
			i--; //Para que no se salte el siguiente elemento por el resize del vector
		}
	}
	//Update cannon
	if(!myCannon->update(deltaTime)) exit = true;
	
	
	//Update lasers
	for (int i = 0; i < lasers.size(); i++) {
		if (!lasers[i]->update(myCannon)) {
			delete lasers[i];
			lasers.erase(lasers.begin() + i);
			i--; //Para que no se salte el siguiente elemento por el resize del vector
		}
	}
	
	//Comprobacion de cambio de direccion de aliens
	if (cantMove) {
		alienDirection = alienDirection * -1;
		cantMove = false;
	}
	if (aliens.size() <= 0) {
		exit = true;
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


void Game::fireLaser(Point2D<int>& pos, bool source) {
	lasers.push_back(new Laser(pos/* Temporal */, source, renderer, this));
}

int Game::getRandomRange(int min, int max) {
	mt19937_64 generator(static_cast<unsigned>(time(nullptr))); //generador que es en funcion del segundo actual(maybe hay que cambiar el time(nulptr))
	uniform_int_distribution<int> random(min, max); //random a generar entre valores
	return random(generator); //el random con la semilla de generator
}

vector<Bunker*> Game::getBunkers()const {
	return bunkers;
}

vector<Alien*> Game::getAliens() const {
	return aliens;
}

