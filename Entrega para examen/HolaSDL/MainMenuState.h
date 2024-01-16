#pragma once
#include "GameState.h"
#include "Button.h"
#include <string>
#include <ostream>

//class PlayState;
class MainMenuState: public GameState
{
private: 
	bool asking = false;
	bool stateChanged = false;
	bool loadMode = false;
	bool escribir = false;
	std::string codigoString;
	Button* newGameButton;
	Button* loadGameButton;
	Button* exitButton; 
	std::unique_ptr<SDL_Rect> rectBox;
	std::unique_ptr<SDL_Rect> rectCode;
	
public:
	MainMenuState(Game* game);
	~MainMenuState(){}
	void update() override;	
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream&) const override;
	void hasDied(GameList<GameObject, true>::anchor) override;

	void changeNewLevel(std::string name);
	void createButtons();
	std::string askLoadNumber();
	void renderTextBox() const;
	void renderTextCodigo() const;
};

