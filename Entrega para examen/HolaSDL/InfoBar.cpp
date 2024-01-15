#include "checkML.h"
#include "InfoBar.h"
#include "Game.h"
InfoBar::InfoBar(Game* _game,std::istream&  entrada,Texture* _texturePoints, Texture* _textureLifes,
	Cannon* _cannon) :
	GameObject(_game),
	pointsTexture(_texturePoints),
	lifesTexture(_textureLifes),
	cannon(_cannon) {
	if (!(entrada >> score))throw FileFormatError("error al leer puntuacion de infoBar", 9);
	setRects();
}

void InfoBar::setRects() {
	//Maxima puntuacion de 6 digitos
	posLifes = { 20, WINDOW_HEIGHT - (lifesTexture->getFrameHeight() + 20) };
	posScore = { WINDOW_WIDTH - (30 + pointsTexture->getFrameWidth() * 6), 
				 WINDOW_HEIGHT - (pointsTexture->getFrameHeight() + 20) }; 

	rectLifes = std::make_unique<SDL_Rect>(SDL_Rect{ posLifes.getX(), posLifes.getY(),  
		lifesTexture->getFrameWidth(), lifesTexture->getFrameHeight()}); 

	rectScore = std::make_unique<SDL_Rect>(SDL_Rect{ posScore.getX(), posScore.getY(),
		pointsTexture->getFrameWidth(), pointsTexture->getFrameHeight()}); 
}
void InfoBar::render()const {
	for (int i = 0; i < cannon->getLifes(); ++i) {
		SDL_Rect lifeRect = { rectLifes->x + i * (rectLifes->w + LIFES_OFFSET),
							rectLifes->y,
							rectLifes->w,
							rectLifes->h };
		lifesTexture->renderFrame(lifeRect, 0, 0);
	}

	//reset del rect
	*rectScore = { posScore.getX(), posScore.getY(),
	pointsTexture->getFrameWidth(), pointsTexture->getFrameHeight() };

	std::string scoreText = std::to_string(score);
	for (char e : scoreText) {
		int aux = e - '0';
		pointsTexture->renderFrame(*rectScore, 0, aux);
		rectScore->x += pointsTexture->getFrameWidth();
	}
}
void InfoBar::update() {}
void InfoBar::addScore(int points) {
	score += points;
}
void InfoBar::save(std::ostream& os) const {
	os << "7 " << score;
}