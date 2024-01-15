#include "checkML.h"
#include "Button.h"
#include "Game.h"
Button::Button(Game* game, Texture* texture, Point2D<int> pos) :
    GameObject(game), 
    texture(texture),
    hover(false),
    rect(std::make_unique<SDL_Rect>(SDL_Rect{ pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight()})) {}

void Button:: render() const
{
    SDL_SetTextureColorMod(texture->getTexture(), 255, 255, 255);
    if (hover) {
        //Cambia color si cursor encima
        SDL_SetTextureColorMod(texture->getTexture(), 0, 255, 0);
    }
    texture->render(*rect);
   
}

void Button:: update()
{
    SDL_Point point;
    SDL_GetMouseState(&point.x, &point.y);

    // Comprueba si el ratón está sobre el rectángulo
    hover = SDL_PointInRect(&point, rect.get());
}
void Button::handleEvent(const SDL_Event& event) {
    // Evento de pulsación de un botón del ratón (y botón izquierdo)
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && hover)  callback();
}

void Button::connect(Button::Callback cb) {
    callback = cb;
}
void Button::save(std::ostream& os) const {};