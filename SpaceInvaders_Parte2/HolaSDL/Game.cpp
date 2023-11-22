
#include "Game.h"




using namespace std;
Game::Game() : window(nullptr), renderer(nullptr), exit(false), lastFrameTime(SDL_GetTicks()), alienDirection(Vector2D<int>(1, 0)), cantMove(false),
TEXTURAS{
		{"aliens.png", 3, 2},
		{"bunker.png", 1, 4},
		{"spaceship.png", 1, 1},
		{"stars.png", 1, 1}
} {


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw "Error al inicializar SDL" ;
		return;
	}
	 
	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		throw  "ERROR: SDL_Window not found";
		SDL_QUIT;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		throw "ERROR: SDL_Renderer not found" ;
		return;
	}

	//Carga texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		 texturas[i] = new Texture(renderer, (TEXTURE_ROOT + TEXTURAS[i].direccion).c_str(), TEXTURAS[i].rows, TEXTURAS[i].cols);
		
	}

	//inicialización por lectura
	readGame();
	
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
	//myCannon->render();
	//Render lasers
	for (int i = 0; i < lasers.size(); i++) {
		lasers[i]->render();
	}
	SDL_RenderPresent(renderer);
}
void Game::update(const Uint32 deltaTime) {
	//Update aliens

	//for (int i = 0; i < aliens.size(); i++) {
	//	if (!aliens[i]->update(deltaTime)) { 
	//		delete aliens[i]; 
	//		aliens.erase(aliens.begin() + i); 
	//		i--; //Para que no se salte el siguiente elemento por el resize del vector
	//	}
	//}
	////Update bunkers
	//for (int i = 0; i < bunkers.size(); i++) {
	//	
	//	if (!bunkers[i]->update()) {
	//		delete bunkers[i]; 
	//		bunkers.erase(bunkers.begin() + i); 
	//		i--; //Para que no se salte el siguiente elemento por el resize del vector
	//	}
	//}
	//Update cannon
	//if (!myCannon->update(deltaTime)) exit = true;
	////Update lasers
	//for (int i = 0; i < lasers.size(); i++) {
	//	if (!lasers[i]->update()) {
	//		delete lasers[i];
	//		lasers.erase(lasers.begin() + i);
	//		i--; //Para que no se salte el siguiente elemento por el resize del vector
	//	}
	//}
	//Update de sceneObjects
	for (auto i = sceneObjects.begin(); i != sceneObjects.end(); i++) {
		(*i)->update();
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
		//myCannon->handleEvents(event);
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
	
	lasers.push_back(new Laser(pos , source, renderer, this));
}

int Game::getRandomRange(int min, int max) {
	
	return uniform_int_distribution<int>(min, max)(rendomGenerator);
}

void Game::readGame() {
	ifstream entrada;
	entrada.open("../mapas/original.txt");
	if (!entrada.is_open()) throw "ERROR: entrada no encontrada.";
	else {
		int tipo, posX, posY, lifes, remainingTime;
		//inicialización de vectores de aliens y bunkers

		while (!entrada.eof()) { //habia que cambiar esto
			//lectura de variables
			entrada >> tipo;
			entrada >> posX;
			entrada >> posY;
			
			//cannon
			if (tipo == 0) {
				entrada >> lifes >> remainingTime;
				Point2D<int> posC = { posX, posY };
				sceneObjects.push_back(new Cannon(posC, texturas[cannon], lifes, remainingTime, this));
			}
			//aliens
			else if (tipo == 1) {
				entrada >> tipo;
				Point2D<int> posC = { posX, posY };
				sceneObjects.push_back(new Alien(this, posC, texturas[alien], tipo));
			}
			else if (tipo == 2) {
				entrada >> tipo;
				Point2D<int> posC = { posX, posY };
				sceneObjects.push_back(new ShooterAlien(this, posC, texturas[alien], tipo));
			}
			//nave nodriza
			else if (tipo == 3) {
				

			}
			//bunker
			else if (tipo == 4) {
				entrada >> lifes;
				Point2D<int> pos = { posX, posY };
				sceneObjects.push_back(new Bunker(pos, lifes, texturas[bunker]));
			}
			//ovni
			else if (tipo == 5) {

			}
			//laser
			else if (tipo == 6) {

			}
		}
	}
}

bool Game::bunkerColision(SDL_Rect* laserRect) {
	for (int i = 0; i < bunkers.size(); i++) {

		if (SDL_HasIntersection(bunkers[i]->getRect(), laserRect)) {
			bunkers[i]->hit(); 
			return false;
		}
	}
	return true;
}
bool Game::laserColision(SDL_Rect* laserRect, bool laserSrcOppo) {
	for (int i = 0; i < lasers.size(); i++) {
		if (SDL_HasIntersection(lasers[i]->getRect(), laserRect) && lasers[i]->getSource() == laserSrcOppo) {
			lasers[i]->setSelfDestroy();
			return true;
		}
	}
	return false;
}
bool Game::alienColision(SDL_Rect* laserRect) { 
	for (int i = 0; i < aliens.size(); i++) {

		if (SDL_HasIntersection(aliens[i]->getRect(), laserRect)) {
			aliens[i]->hit();
			return true;
		}
	}
	return false;
}
bool Game::cannonColision(SDL_Rect* laserRect) {
	if (SDL_HasIntersection(myCannon->getRect(), laserRect)) {
		myCannon->hit();
		return true;
	}
	return false;
}
