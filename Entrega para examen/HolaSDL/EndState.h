#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "Button.h"
#include "SDL.h"
class EndState : public GameState
{
private:
	bool victory;
	Button* loadMenuButton;
	Button* exitButton;
	
public:
	EndState(Game* game, bool victory);
	~EndState();
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream&) const override;
	void hasDied(GameList<GameObject, true>::anchor) override;

	void createButtons();
	void changeToMenu();
};

