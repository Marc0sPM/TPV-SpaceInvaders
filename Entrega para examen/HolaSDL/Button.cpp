#include "Button.h"
#include "Game.h"
#include "checkML.h"

Button::Button(Game* game, Texture* texture, Point2D<int> pos) 
    :
    GameObject(game),
    texture(texture),
    rect(std::make_unique<SDL_Rect>(SDL_Rect{ pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() })) {}

Button::~Button() {
    delete texture;
}

void Button::render() const {
    SDL_SetTextureColorMod(texture->getTexture(), 255, 255, 255);

    if (hover) {
        //Cambia de color cuando el cursor esta encima
        SDL_SetTextureColorMod(texture->getTexture(), 0, 255, 0);
    }

    texture->render(*rect);
}
void Button :: update() {
    //Detecta si el cursor esta encima del boton
    SDL_Point point;
    SDL_GetMouseState(&point.x, &point.y);
    hover = SDL_PointInRect(&point, rect.get());
}
void Button::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && hover) {
        callback();
    }
}
void Button::connect(Button::Callback cb) {
    callback = cb;
}
void Button::save(std::ostream& os) const {};