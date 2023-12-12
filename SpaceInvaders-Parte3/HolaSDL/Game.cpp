
#include "Game.h"


Game::Game() : window(nullptr), renderer(nullptr), exit(false), lastFrameTime(SDL_GetTicks()),
alienDirection(Vector2D<int>(1, 0)),
cantMove(false),
mothership(new Mothership(this))
{
	//Inicializacion de SDL 
	initializeSDL(); 
	//Carga texturas 
	loadTextures(); 
	//inicialización por lectura
	readGame("../mapas/original.txt");
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
		if (!isPause) {
			
			update();
			render();
			if (mothership->haveLanded() || mothership->getCont() <= 0 || _cannon->getLifes() <= 0) exit = true;
		}
		
	}
}

void Game::render() const {

	SDL_RenderClear(renderer);
	//Render aliens
	texturas[background]->render();
	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); it++) {
		(*it)->render();
	}
	infoBar->render();
	SDL_RenderPresent(renderer);
}

void Game::update() {

	//Update de sceneObjects
	
	mothership->update();

	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); it++) {
		(*it)->update();
	}


	for (auto it = toDelete.begin(); it != toDelete.end(); ++it) {
		delete* (*it);
		sceneObjects.erase(*it);
	}
	toDelete.clear(); 

}
void Game::handleEvents() {
	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		_cannon->handleEvents(event);
		playerInput(event);
		
	}
}

void Game::playerInput(const SDL_Event& event) {
	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_p: isPause = !isPause;
			break;
		case SDLK_q: exit = true;
			break;
		case SDLK_s:
			//para que solo sea en save
			isPause = true;
			save = true;
			saveNum = -1;
			std::cout << "Presiona un numero del 0 al 9 para guardar: ";
			break;
		case SDLK_l:
			//para que solo sea en load
			isPause = true;
			load = true;
			saveNum = -1;
			std::cout << "Presiona un numero del 0 al 9 para cargar: ";
			break;
		case SDLK_0:
		case SDLK_1:
		case SDLK_2:
		case SDLK_3:
		case SDLK_4:
		case SDLK_5:
		case SDLK_6:
		case SDLK_7:
		case SDLK_8:
		case SDLK_9:
			try {
				if (save) {
					ofstream os;
					saveNum = event.key.keysym.sym - SDLK_0;
					saveGame(os, save, saveNum);
				}
				else if (load) {
					saveNum = event.key.keysym.sym - SDLK_0;
					loadGame(saveNum, load);
				}
			}
			catch (const InvadersError& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
			break;
		}
	}
}
		
void Game::saveGame(ofstream& os, bool& save, int& saveNum) {
	string file = "saved" + std::to_string(saveNum) + ".txt";
	os.open("../mapas/save/" + file);
	if (os.is_open()) {
		for (auto it = sceneObjects.begin(); it != sceneObjects.end(); it++) {
			(*it)->save(os);
			os << std::endl;
		}
		infoBar->save(os);
		os.close();
		std::cout << "SAVED" << std::endl;

		//Se cierra igual como el año pasado
		os.close();
		isPause = false;
	}
	else {
		std::cerr << "ERROR: el juego no se ha podido guardar" << std::endl;
	}
	save = false;
}

void Game::loadGame(int& saveNum, bool& load) {
	string file = "saved" + std::to_string(saveNum) + ".txt";
	//Eliminar objetos
	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		delete* it;
	}
	sceneObjects.clear();
	
	//delete infoBar //NO VA Y PETA EL JUEGO, SE SUPONE QUE LOS METODOS ESTAN BIEN
	load = false;
	readGame("../mapas/save/" + file);
	isPause = false;
}
	


//Añade un laser a la lista de objetos
void Game::fireLaser(Point2D<int>& pos, char source) {
	Laser* l = new Laser(pos, source, this);
	sceneObjects.push_back(l);
	l->setListIterator(--sceneObjects.end());
	
}
//elimina objeto de la lista
void Game::hasDied(list<SceneObject*>::iterator& iterator) {
	toDelete.push_back(iterator);
	increaseScore(*iterator);
}

bool Game::damage(SDL_Rect* laserRect, char& src) {
	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) {
		if ((*it)->hit(laserRect, src)) return true;
	}
	return false;
}
int Game::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}
void Game::increaseScore(SceneObject* object) {
	if (dynamic_cast<Alien*>(object)) {
		Alien* alien = dynamic_cast<Alien*>(object);
		if (alien->getType() == 0) infoBar->addScore(SHOOTER_POINTS); 
		else if (alien->getType() == 1) infoBar->addScore(GREEN_POINTS);
		else if (alien->getType() == 2) infoBar->addScore(RED_POINTS);
	}
	else if (dynamic_cast<Ufo*>(object)) {
		infoBar->addScore(UFO_POITNS);
	}
}


#pragma region INICIALIZACION DEL JUEGO 
void Game::loadTextures() {
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		texturas[i] = new Texture(renderer, (TEXTURE_ROOT + TEXTURAS[i].direccion).c_str(), TEXTURAS[i].rows, TEXTURAS[i].cols);
	}
}
void Game::initializeSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw SDLError("Error al inicializar SDL");
	}

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		throw  SDLError("ERROR: SDL_Window not found");
	}
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		throw SDLError("ERROR: SDL_Renderer not found");
	}
}
void Game::readGame(string file) {
	ifstream entrada;
	
	entrada.open(file);

	if (!entrada.is_open()) throw FileNotFoundError("ERROR: entrada no encontrada.");
	else {
		int object, posX, posY;
		//inicialización de vectores de aliens y bunkers

		while (entrada >> object) {
			//lectura de variables

			if (object == 7)
				readInfoBar(entrada);
			else {
				entrada >> posX;
				entrada >> posY;
				//cannon
				if (object == 0) readCannon(entrada, posX, posY);
				//aliens
				else if (object == 1) readAliens(entrada, posX, posY);
				//shooter alien
				else if (object == 2)  readShooterAliens(entrada, posX, posY);
				//bunker
				else if (object == 4)  readBunkers(entrada, posX, posY);
				//ufo
				else if (object == 5) readUfo(entrada, posX, posY);
				//laser
				else if (object == 6) readLasers(entrada, posX, posY);
			}
		}
		entrada.close();
	}
}

void Game::setToList(SceneObject* object) {
	sceneObjects.push_back(object);
	object->setListIterator(--sceneObjects.end());
}

void Game::readAliens(istream& entrada, int posX, int posY) {
	int tipo;
	entrada >> tipo;
	Point2D<int> posC = { posX, posY };
	Alien* a = new Alien(this, posC, texturas[alien], tipo, mothership);
	setToList(a);
	mothership->addAlien();
}
void Game::readBunkers(istream& entrada, int posX, int posY) {
	int lifes;
	entrada >> lifes;
	Point2D<int> pos = { posX, posY };
	Bunker* b = new Bunker(this, pos, lifes, texturas[bunker]);
	setToList(b);

}
void Game::readCannon(istream& entrada, int posX, int posY) {
	int lifes, remainingTime;
	entrada >> lifes;
	entrada >> remainingTime;
	Point2D<int> posC = { posX, posY };
	_cannon = new Cannon(posC, lifes, remainingTime, this, texturas[cannon]);
	setToList(_cannon);
	

}
void Game::readShooterAliens(istream& entrada, int posX, int posY) {
	int reloadTime, tipo;
	entrada >> tipo >> reloadTime;
	Point2D<int> posC = { posX, posY };
	ShooterAlien* s = new ShooterAlien(this, posC, texturas[alien], tipo, reloadTime, mothership);
	setToList(s);
	mothership->addAlien();
}
void Game::readUfo(istream& entrada, int posX, int posY) {
	int randomShownTime, state;
	entrada >> state >> randomShownTime;
	Point2D<int> posC = { posX, posY };
	Ufo* u = new Ufo(this, posC, texturas[ufo], randomShownTime, state);
	setToList(u);
}
void Game::readInfoBar(istream& entrada) {
	int score;
	entrada >> score;
	infoBar = new InfoBar(this, texturas[numbers], texturas[cannon], _cannon, score);
}
void Game::readLasers(istream& entrada, int posX, int posY) {
	char color;
	entrada >> color;
	Point2D<int> pos = { posX, posY };
	Laser* l = new Laser(pos, color, this);
	setToList(l);
}
#pragma endregion
