#include "checkML.h"
#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"
MainMenuState::MainMenuState(Game* game): 
    GameState(game), 
    rectBox(std::make_unique<SDL_Rect>(SDL_Rect{ 250, 200, game->getTexture(TextureName::BOX)->getFrameWidth(), game->getTexture(TextureName::BOX)->getFrameHeight() })),
    rectCode(std::make_unique<SDL_Rect>(SDL_Rect{ 320, 220, game->getTexture(TextureName::CODIGO)->getFrameWidth(), game->getTexture(TextureName::CODIGO)->getFrameHeight() })){
    createButtons();
}

void MainMenuState::update() {
    // Renderizar botones
    if (!loadMode) {
        for (auto& button : gameObjects)
        {
            button.update();
        }
    }
}
void MainMenuState::render() const {
  
    if (game->getTexture(TextureName::MAIN_MENU)) {
        SDL_Rect backgroundRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
        game->getTexture(TextureName::MAIN_MENU)->renderFrame(backgroundRect, 0, 0);
    }
    // Renderizar botones
    for (const auto& button : gameObjects)
    {
        button.render();
    }
    if (loadMode) {
        renderTextBox();
    }
}
void MainMenuState::handleEvent(const SDL_Event& event) {
    if (!loadMode) {
        for (const auto& button : eventHandlers)
        {
            button->handleEvent(event);
        }

    }
    if ((loadMode) && event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RETURN) {
            if (loadMode) {
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
void MainMenuState::save(ostream&) const {}
void MainMenuState::hasDied(GameList<GameObject, true>::anchor) {}

void MainMenuState::createButtons() {
    // Crear botones para el menú principal

    newGameButton = new Button(game, game->getTexture(TextureName::NEW_GAME), 
        Point2D<int>(WINDOW_WIDTH/2 - game->getTexture(TextureName::NEW_GAME)->getFrameWidth()/2, 140));

    loadGameButton = new Button(game, game->getTexture(TextureName::LOAD_GAME),
        Point2D<int>(WINDOW_WIDTH/2 - game->getTexture(TextureName::LOAD_GAME)->getFrameWidth()/2, 200));

    exitButton = new Button(game, game->getTexture(TextureName::EXIT), 
        Point2D<int>(WINDOW_WIDTH/2 - game->getTexture(TextureName::EXIT)->getFrameWidth() / 2, 260));

    addObject(newGameButton);
    addEventListener(newGameButton);

    addObject(loadGameButton);
    addEventListener(loadGameButton);

    addObject(exitButton);
    addEventListener(exitButton);
    
    newGameButton->connect([this]() {
        
        changeNewLevel(NEWGAME_ROOT);
        });
    loadGameButton->connect([this]() {
        loadMode = true;
        });

    exitButton->connect([this]() {
        game->exitGame();
        });
}

void MainMenuState::changeNewLevel(string name) {
    //newPlaySate = new PlayState(game, name);
   
    //ver que se hace luego
    game->getGameStateMachine()->replaceState(std::make_shared<PlayState>(game, name));
    stateChanged = true;
}
std::string MainMenuState::askLoadNumber() {
    
    return "2";
}
void MainMenuState::renderTextBox() const {

    game->getTexture(TextureName::BOX)->renderFrame(*rectBox, 0, 0);
    game->getTexture(TextureName::CODIGO)->renderFrame(*rectCode, 0, 0);
    if (escribir && !codigoString.empty())
        renderTextCodigo();
}
void MainMenuState::renderTextCodigo() const {

    // Crear una superficie de texto
    SDL_Surface* textSurface = TTF_RenderText_Solid(game->getFont(), codigoString.c_str(), { 255, 255, 255 }); // Color blanco

    // Crear una textura a partir de la superficie
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->getRenderer(), textSurface);

    // Obtener las dimensiones del texto
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Crear un rectángulo para la posición y tamaño del texto
    SDL_Rect rect = { rectBox->x + 80, rectBox->y + 80, textWidth, textHeight };

    // Renderizar la textura en el renderer
    SDL_RenderCopy(game->getRenderer(), textTexture, nullptr, &rect);
}

