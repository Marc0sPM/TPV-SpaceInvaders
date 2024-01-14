#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"
#include "checkML.h"
MainMenuState::MainMenuState(Game* game)
	:
	GameState(game)
{
	createButtons();
}
MainMenuState::~MainMenuState() {
}
void MainMenuState::createButtons() {
	//Boton cargar nueva partida
	newGameButton = std::make_unique<Button>(game, game->getTexture(TextureNames::NEW_GAME),
		Point2D<int>(WINDOW_WIDTH / 2 - game->getTexture(TextureNames::NEW_GAME)->getFrameWidth() / 2, 140));
	//Boton cargar partida guardada
	loadGameButton = std::make_unique<Button>(game, game->getTexture(TextureNames::LOAD_GAME),
		Point2D<int>(WINDOW_WIDTH / 2 - game->getTexture(TextureNames::LOAD_GAME)->getFrameWidth() / 2, 200));
	//Boton para salir
	exitButton = std::make_unique<Button>(game, game->getTexture(TextureNames::EXIT),
		Point2D<int>(WINDOW_WIDTH / 2 - game->getTexture(TextureNames::EXIT)->getFrameWidth() / 2, 260));

	//Se añaden los botones a las listas correspondientes
	addObject(newGameButton.get());
	addEventListener(newGameButton.get());

	addObject(loadGameButton.get());
	addEventListener(loadGameButton.get());

	addObject(exitButton.get());
	addEventListener(exitButton.get());

	//Se establecen las callbacks de cada boton
	newGameButton->connect([this]() {
		cout << "nueva partida";
		/*changeNewLevel(NEWGAME_ROOT);*/
		});

	loadGameButton->connect([this]() {
		cout <<  "cargar partida guardada";
		/*string fullName;
		fullName = LOADGAME_ROOT + "saved" + ".txt";
		changeNewLevel(fullName);*/
		});

	exitButton->connect([this]() {
		game->exitGame();
		});
}
void MainMenuState::changeNewLevel(string name) {
	//PlayState* newPlaySate = new PlayState(game, name);
	//game->getGameStateMachine()->replaceState(newPlaySate);
}
void MainMenuState::update(){
	for (auto& button : gameObjects) {
		button.update();
	}
}
void MainMenuState::render()const{
	game->getTexture(TextureNames::MAIN_MENU)->render();
	for (auto& button : gameObjects) {
		button.render();
	}
}
void MainMenuState::handleEvent(const SDL_Event& event){
	for (auto& button : eventListeners) {
		button->handleEvent(event);
	}
}
void MainMenuState::save(std::ostream& os)const {};
void MainMenuState::hasDied(GameList<GameObject, true>::anchor){}