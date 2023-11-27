
#include "Game.h"


Game::Game() : window(nullptr), renderer(nullptr), exit(false), lastFrameTime(SDL_GetTicks()),
alienDirection(Vector2D<int>(1, 0)),
cantMove(false),
mothership(new Mothership(this)),
TEXTURAS{
	{"aliens.png", 3, 2},
	{"bunker.png", 1, 4},
	{"spaceship.png", 1, 1},
	{"stars.png", 1, 1},
	{"ufo.png", 1, 2}, 
	{"numbers.png", 1, 10}}
{
	//Inicializacion de SDL 
	initializeSDL(); 
	//Carga texturas 
	loadTextures(); 
	//inicialización por lectura
	readGame();
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
		update();
		render();
		if (mothership->haveLanded() || mothership->getCont() <= 0) exit = true;
	}
}

void Game::render() const {

	SDL_RenderClear(renderer);
	//Render aliens
	texturas[background]->render();
	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); it++) {
		(*it)->render();
	}
	SDL_RenderPresent(renderer);
}

void Game::update() {

	//Update de sceneObjects
	
	mothership->update();

	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); it++) {
		(*it)->update();
	}



	auto it = sceneObjects.begin();
	while (it != sceneObjects.end()) {
		auto currentObj = *it;
		
		
		if (currentObj->ShouldRemove()) {
			hasDied(it);
		}
		else ++it;
	}
}
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		for (auto it = sceneObjects.begin(); it != sceneObjects.end(); it++) {
			SceneObject* currentObj = *it;

			if (dynamic_cast<Cannon*>(currentObj) != nullptr) {
				Cannon* cannon = dynamic_cast<Cannon*>(currentObj);
				cannon->handleEvents(event);
				break;
			}
		}
		
	}
}

//Añade un laser a la lista de objetos
void Game::fireLaser(Point2D<int>& pos, char source) {
	Laser* l = new Laser(pos, source, this);
	sceneObjects.push_back(l);
	l->setListIterator(--sceneObjects.end());
	
}
//elimina objeto de la lista
void Game::hasDied(list<SceneObject*>::iterator& iterator) {
	auto it = iterator;
	iterator++;

	delete* it;
	sceneObjects.erase(it);
}

bool Game::damage(SDL_Rect* laserRect, char& src) {
	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		SceneObject* currentObj = *it;
		if (currentObj->hit(laserRect, src)) return true;
	}
	return false;
}
int Game::getRandomRange(int min, int max) {

	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}


#pragma region INICIALIZACION DEL JUEGO 
void Game::loadTextures() {
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		texturas[i] = new Texture(renderer, (TEXTURE_ROOT + TEXTURAS[i].direccion).c_str(), TEXTURAS[i].rows, TEXTURAS[i].cols);
	}
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
	entrada.open("../mapas/urgente.txt");
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

			//bunker
			else if (object == 4)  readBunkers(entrada, posX, posY);
			//ufo
			else if (object == 5) readUfo(entrada, posX, posY);
			//laser
			else if (object == 6);
			

		}
	}
}

void Game::readAliens(istream& entrada, int posX, int posY) {
	int tipo;
	entrada >> tipo;
	Point2D<int> posC = { posX, posY };
	Alien* a = new Alien(this, posC, texturas[alien], tipo, mothership);
	sceneObjects.push_back(a);
	a->setListIterator(--sceneObjects.end());
	mothership->addAlien();
}
void Game::readBunkers(istream& entrada, int posX, int posY) {
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
	cannonY = c->getPos().getY();

}
void Game::readShooterAliens(istream& entrada, int posX, int posY) {
	int reloadTime, tipo;
	entrada >> tipo >> reloadTime;
	Point2D<int> posC = { posX, posY };
	ShooterAlien* s = new ShooterAlien(this, posC, texturas[alien], tipo, reloadTime, mothership);
	sceneObjects.push_back(s);
	s->setListIterator(--sceneObjects.end());
	mothership->addAlien();
}
void Game::readUfo(istream& entrada, int posX, int posY) {
	int randomShownTime;
	entrada >> randomShownTime;
	Point2D<int> posC = { posX, posY };
	Ufo* u = new Ufo(this, posC, texturas[ufo], randomShownTime);
	sceneObjects.push_back(u);
	u->setListIterator(--sceneObjects.end());
}
#pragma endregion


//ELIMINAR MAS TARDE
//bool Game::bunkerColision(SDL_Rect* laserRect) {
//	for (int i = 0; i < bunkers.size(); i++) {
//
//		if (SDL_HasIntersection(bunkers[i]->getRect(), laserRect)) {
//			bunkers[i]->hit();
//			return false;
//		}
//	}
//	return true;
//}
//bool Game::laserColision(SDL_Rect* laserRect, bool laserSrcOppo) {
//	for (int i = 0; i < lasers.size(); i++) {
//		if (SDL_HasIntersection(lasers[i]->getRect(), laserRect) && lasers[i]->getSource() == laserSrcOppo) {
//			lasers[i]->setSelfDestroy();
//			return true;
//		}
//	}
//	return false;
//}
//bool Game::alienColision(SDL_Rect* laserRect) {
//	for (int i = 0; i < aliens.size(); i++) {
//
//		/*if (SDL_HasIntersection(aliens[i]->getRect(), laserRect)) {
//			aliens[i]->hit();
//			return true;
//		}*/
//	}
//	return false;
//}
//bool Game::cannonColision(SDL_Rect* laserRect) {
//	if (SDL_HasIntersection(myCannon->getRect(), laserRect)) {
//		myCannon->hit();
//		return true;
//	}
//	return false;
//}
