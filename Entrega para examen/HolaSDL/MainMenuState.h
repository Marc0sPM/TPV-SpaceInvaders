#pragma once
#include "GameState.h"
#include "Button.h"
#include <string>
#include <ostream>

class MainMenuState : public GameState
{
private:
	//bool asking -> preguntar numero en load
	bool stateChanged = false;
	//Botones de la escena
	std::unique_ptr<Button> newGameButton;
	std::unique_ptr<Button> loadGameButton;
	std::unique_ptr<Button> exitButton;
public:
	MainMenuState(Game* game);
	//Destructora
	~MainMenuState();
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream&) const/* override*/;
	void hasDied(GameList<GameObject, true>::anchor) /*override*/;
	// Metodo auxiliar para cargar cualquier nivel dado el nombre del archivo de entrada
	void changeNewLevel(std::string name);
	void createButtons();
	std::string askLoadNumber();
};

