
#include "Game.h"
using namespace std;
Game::Game() : window(nullptr), renderer(nullptr), exit(false), lastFrameTime(SDL_GetTicks()), 
	alienDirection(Vector2D<int>(1, 0)), 
	cantMove(false),
	TEXTURAS{
		{"aliens.png", 3, 2},
		{"bunker.png", 1, 4},
		{"spaceship.png", 1, 1},
		{"stars.png", 1, 1}
		} {
	//Inicializacion de SDL
	initializeSDL();
	//Carga texturas
	loadTextures();
	//inicialización por lectura
	readGame();
	motherShip = new MotherShip(this, cantAliens);
}
Game :: ~Game() {
	
	//Eliminacion dinamica de la lista de SceneObjects
	for (auto& it : sceneObjects) { 
		delete it;
	}

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

				 //
		render();//cambiar de orden posteriormente
		update();//
	}
}

void Game::render() const{

	SDL_RenderClear(renderer);
	//Render aliens
	texturas[background]->render();
	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); it++) {
		(*it)->render();
	}
	motherShip->render(); //no se que deberia de hacer la motherShip
	SDL_RenderPresent(renderer);
}

void Game::update() {
	
	//Update de sceneObjects
	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); it++) {
		(*it)->update();
	}

	//Comprobacion de cambio de direccion de aliens
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
		//myCannon->handleEvents(event);
	}
}

//Añade un laser a la lista de objetos
void Game::fireLaser(Point2D<int>& pos, bool source) {
	
	sceneObjects.push_back(new Laser(pos , source, this));
}
//elimina objeto de la lista
void Game::hasDied(list<SceneObject*>::iterator iterator) {
	delete *iterator; 
	sceneObjects.erase(iterator);
}

// Calcula y devuelve la dirección común de movimiento de los Aliens
Vector2D<int> Game::getDirection() const {

	return Vector2D<int>(1,0);

}
//Si uno de los aliens choca con los laterales de la pantalla habilita cambio direccion
void Game::cannotMove() {
	cantMove = true;
}

int Game::getRandomRange(int min, int max) const {
	
	return uniform_int_distribution<int>(min, max)(rendomGenerator);
}

#pragma region INICIALIZACION DEL JUEGO 
void Game::loadTextures() {
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		texturas[i] = new Texture(renderer, (TEXTURE_ROOT + TEXTURAS[i].direccion).c_str(), TEXTURAS[i].rows, TEXTURAS[i].cols); }
}
void Game::initializeSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw "Error al inicializar SDL";
	}

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		throw  "ERROR: SDL_Window not found";
	}
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		throw "ERROR: SDL_Renderer not found";
	}
}
void Game::readGame() {
	ifstream entrada;
	entrada.open("../mapas/original.txt");
	if (!entrada.is_open()) throw "ERROR: entrada no encontrada.";
	else {
		int object, posX, posY;
		//inicialización de vectores de aliens y bunkers

		while (!entrada.eof()) { //habia que cambiar esto
			//lectura de variables
			entrada >> object;
			entrada >> posX;
			entrada >> posY;
			//cannon
			if (object == 0) readCannon(entrada, posX, posY);
			//aliens
			else if (object == 1) readAliens(entrada, posX, posY);

			else if (object == 2)  readShooterAliens(entrada, posX, posY);

			//mothership
			else if (object == 3);

			//bunker
			else if (object == 4)  readBunkers(entrada, posX, posY);

			//ovni
			else if (object == 5);

			//laser
			else if (object == 6);

			
		}
	}
}

void Game::readAliens(istream& entrada, int posX, int posY) {
	int tipo;
	entrada >> tipo;
	Point2D<int> posC = { posX, posY }; 
	Alien* a = new Alien(this, posC, texturas[alien], tipo, motherShip); 
	sceneObjects.push_back(a); 
	a->setListIterator(--sceneObjects.end()); 
	cantAliens++;
	
}
void Game::readBunkers(istream& entrada,int posX, int posY) {
	int lifes;
	entrada >> lifes;
	Point2D<int> pos = { posX, posY };
	Bunker* b = new Bunker(this, pos, lifes, texturas[bunker]);
	sceneObjects.push_back(b);
	b->setListIterator(--sceneObjects.end());
	
}
void Game::readCannon(istream& entrada, int posX, int posY) {
	int lifes, remainingTime;
	entrada >> lifes;
	entrada >> remainingTime;
	Point2D<int> posC = { posX, posY };
	Cannon* c = new Cannon(posC, lifes, remainingTime, this, texturas[cannon]);
	sceneObjects.push_back(c);
	c->setListIterator(--sceneObjects.end());
	
}
void Game::readShooterAliens(istream& entrada, int posX, int posY) {
	int reloadTime, tipo;
	entrada >> tipo >> reloadTime;
	Point2D<int> posC = { posX, posY };
	ShooterAlien* s = new ShooterAlien(this, posC, texturas[alien], tipo, reloadTime, motherShip);
	sceneObjects.push_back(s);
	s->setListIterator(--sceneObjects.end());
	cantAliens++;
}
#pragma endregion

//ELIMINAR MAS TARDE
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

		/*if (SDL_HasIntersection(aliens[i]->getRect(), laserRect)) {
			aliens[i]->hit();
			return true;
		}*/
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
