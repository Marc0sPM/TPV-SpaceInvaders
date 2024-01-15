
#include "checkML.h"
#include "PauseState.h"
#include "EndState.h"
#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"
#include "Exceptions.h"
PauseState::PauseState(Game* game, PlayState* playState) :
    GameState(game),
    playState(playState),
    destRect(make_unique<SDL_Rect>(SDL_Rect{ 250, 200, game->getTexture(TextureName::BOX)->getFrameWidth(), game->getTexture(TextureName::BOX)->getFrameHeight() })),
    destRectCodigo(make_unique<SDL_Rect>(SDL_Rect{ 320, 220, game->getTexture(TextureName::CODIGO)->getFrameWidth(), game->getTexture(TextureName::CODIGO)->getFrameHeight() }))
{
    createButtons();
}

void PauseState::update() {
    if (canExit) {
        game->getGameStateMachine()->popState();
    }
    // Renderizar botones
    if (!codigoMode && !loadMode) {
        for (auto& button : gameObjects)
        {
            button.update();
        }

    }

}

void PauseState::render() const {

    // Renderizar botones

    for (const auto& button : gameObjects)
    {
        button.render();
    }
    if (codigoMode || loadMode) {
        renderTextBox();
    }
}

void PauseState::handleEvent(const SDL_Event& event) {
    if (!codigoMode && !loadMode) {
        for (const auto& button : eventHandlers)
        {
            button->handleEvent(event);
        }

    }
    if ((codigoMode || loadMode) && event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RETURN) {
            if (codigoMode) {
                codigoMode = false;
                savedGame(codigoString);
                codigoString = "";
            }
            else if (loadMode) {
                try {
                    loadMode = false;
                    string fullName;
                    fullName = LOADGAME_ROOT + codigoString + ".txt";
                    changeNewLevel(fullName);

                }
                catch (const FileNotFoundError& e) {
                    SDL_ShowSimpleMessageBox(1, "", e.what(), game->getWindow());
                }
            }
            codigo = true;

        }
        else if (event.key.keysym.sym == SDLK_BACKSPACE && !codigoString.empty()) {
            // Eliminar el último carácter si se presiona Retroceso
            codigoString.pop_back();
        }
        else if (isalpha(event.key.keysym.sym) || isdigit(event.key.keysym.sym)) {
            // Agregar caracteres al código si son alfanuméricos
            codigoString += event.key.keysym.sym;
            escribir = true;
        }

    }

}
void PauseState::save(ostream& os) const {}
void PauseState::hasDied(GameList<GameObject, true>::anchor) {}

void PauseState::savedGame(std::string codigoString) {
    playState->saveGame("../mapas/save/" + codigoString + ".txt");
}

void PauseState::createButtons() {
    continueButton = new Button(game, game->getTexture(TextureName::CONTINUE),
        Point2D<int>(400 - game->getTexture(TextureName::CONTINUE)->getFrameWidth() / 2, 100));

    saveButton = new Button(game, game->getTexture(TextureName::SAVE_GAME),
        Point2D<int>(400 - game->getTexture(TextureName::SAVE_GAME)->getFrameWidth() / 2, 200));

    loadButton = new Button(game, game->getTexture(TextureName::LOAD_GAME),
        Point2D<int>(400 - game->getTexture(TextureName::LOAD_GAME)->getFrameWidth() / 2, 300));

    exitButton = new Button(game, game->getTexture(TextureName::EXIT),
        Point2D<int>(400 - game->getTexture(TextureName::EXIT)->getFrameWidth() / 2, 400));

    addObject(continueButton);
    addEventListener(continueButton);

    addObject(saveButton);
    addEventListener(saveButton);

    addObject(loadButton);
    addEventListener(loadButton);

    addObject(exitButton);
    addEventListener(exitButton);

    continueButton->connect([this]() {

        game->getGameStateMachine()->popState();
        });

    saveButton->connect([this]() {
        codigoMode = true;
        
        });

    loadButton->connect([this]() {
        loadMode = true;
        });

    exitButton->connect([this]() {
        game->getGameStateMachine()->replaceState(std::make_shared<MainMenuState>(game));
        });
}

void PauseState::continueLevel() {

    canExit = true;

}

void PauseState::changeNewLevel(string name) {
    playState->loadGame(name);
    game->getGameStateMachine()->popState();
}

std::string PauseState::askLoadNumber() {

    return "2";
}

void PauseState::renderTextBox() const {

    game->getTexture(TextureName::BOX)->renderFrame(*destRect, 0, 0);
    game->getTexture(TextureName::CODIGO)->renderFrame(*destRectCodigo, 0, 0);
    if(escribir && !codigoString.empty())
    renderTextCodigo();
}
void PauseState::renderTextCodigo() const {
    
        // Crear una superficie de texto
        SDL_Surface* textSurface = TTF_RenderText_Solid(game->getFont(), codigoString.c_str(), { 255, 255, 255 }); // Color blanco

        // Crear una textura a partir de la superficie
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->getRenderer(), textSurface);

        // Obtener las dimensiones del texto
        int textWidth = textSurface->w;
        int textHeight = textSurface->h;

        // Crear un rectángulo para la posición y tamaño del texto
        SDL_Rect rect = { destRect->x + 80, destRect->y + 80, textWidth, textHeight };

        // Renderizar la textura en el renderer
        SDL_RenderCopy(game->getRenderer(), textTexture, nullptr, &rect);
}