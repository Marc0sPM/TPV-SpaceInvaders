#pragma once
#include "GameState.h"
#include "PlayState.h"
#include "Button.h"
#include "texture.h"
#include "SDL.h"
#include <memory>


class PauseState : public GameState
{
private:
	std::unique_ptr<SDL_Rect> destRect;
	std::unique_ptr<SDL_Rect> destRectCodigo;
	bool codigo = false;
	bool canExit = false;
	PlayState* playState;
	Button* continueButton;
	Button* saveButton;
	Button* loadButton;
	Button* exitButton;
	bool codigoMode = false;
	bool loadMode = false;
	bool escribir = false;
	std::string codigoString;

public:
	PauseState(Game* game, PlayState* playState);
	~PauseState();
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream& os) const override;
	void hasDied(GameList<GameObject, true>::anchor) override;

	void renderTextBox() const;
	void renderTextCodigo() const;
	void createButtons();
	std::string askLoadNumber();
	void changeNewLevel(std::string name);

	void savedGame(std::string codigoString);
};