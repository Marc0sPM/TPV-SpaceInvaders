#include "checkML.h"
#include "EndState.h"
#include "Game.h"

EndState::EndState(Game* game, bool victory) 
    : 
    GameState(game), 
    victory(victory) 
{
	createButtons();
}
EndState::~EndState(){}

void EndState::update() {
    // Renderizar botones
    for (auto& button : gameObjects)
    {
        button.update();
    }
}

void EndState::render() const {

    if (victory) {
        Texture* auxTexture = game->getTexture(TextureName::WIN);
        SDL_Rect rect  = {WINDOW_WIDTH / 2 - auxTexture->getFrameWidth(), 100, 500, 150 };
        SDL_SetTextureColorMod(auxTexture->getTexture(), 0, 255, 0);
        game->getTexture(TextureName::WIN)->renderFrame(rect, 0, 0);
    }
    else {
        Texture* auxTexture = game->getTexture(TextureName::GAMEOVER);
        SDL_Rect rect = {WINDOW_WIDTH/ 2 - auxTexture->getFrameWidth(), 100, 500, 150 };
        SDL_SetTextureColorMod(auxTexture->getTexture(), 255, 0, 0);
        game->getTexture(TextureName::GAMEOVER)->renderFrame(rect, 0, 0);
    }
    // Renderizar botones
    for (const auto& button : gameObjects)
    {
        button.render();
    }
}

void EndState::handleEvent(const SDL_Event& event) {
    for (const auto& button : eventHandlers)
    {
        button->handleEvent(event);
    }

}

void EndState::save(std::ostream&) const {}
void EndState::hasDied(GameList<GameObject, true>::anchor) {}

void EndState::createButtons() {

    loadMenuButton = new Button(game, game->getTexture(TextureName::RETURN),
        Point2D<int>(WINDOW_WIDTH/2 - game->getTexture(TextureName::RETURN)->getFrameWidth() / 2, 300));

    exitButton = new Button(game, game->getTexture(TextureName::EXIT),
        Point2D<int>(WINDOW_WIDTH/2 - game->getTexture(TextureName::EXIT)->getFrameWidth() / 2, 360));

    addObject(loadMenuButton);
    addEventListener(loadMenuButton);

    addObject(exitButton);
    addEventListener(exitButton);

    loadMenuButton->connect([this]() {
        changeToMenu();
        });

    exitButton->connect([this]() {
        game->getGameStateMachine()->popState();
        game->exitGame();
        });
}

void EndState::changeToMenu() {
    game->getGameStateMachine()->replaceState(new MainMenuState(game));
}
