#include "InfoBar.h"
#include "Game.h"
InfoBar::InfoBar(Game* _game, Texture* _texturePoints, Texture* _textureLifes,
Cannon* _cannon, int _score) :
GameObject(_game),
pointsTexture(_texturePoints),
lifesTexture(_textureLifes),
score(_score),
cannon(_cannon){
	posLifes = { 20, (int)windowHeight - (lifesTexture->getFrameHeight() + 20) };
	//Maxima puntuacion de 6 digitos
	posScore = { (int)windowWidth - (30 + pointsTexture->getFrameWidth() * 6),  
				 (int)windowHeight - (pointsTexture->getFrameHeight() + 20) };
	
	destRectLifes = new SDL_Rect{ posLifes.getX(), posLifes.getY(),
		lifesTexture->getFrameWidth(), lifesTexture->getFrameHeight() };
	rectScore = new SDL_Rect{ posScore.getX(), posScore.getY(),
		pointsTexture->getFrameWidth(), pointsTexture->getFrameHeight() };
}
void InfoBar::render()const {
	for (int i = 0; i < cannon->getLifes(); ++i) {
		SDL_Rect lifeRect = { destRectLifes->x + i * (destRectLifes->w + LIFES_OFFSET),
							destRectLifes->y,
							destRectLifes->w,
							destRectLifes->h };
		lifesTexture->renderFrame(lifeRect, 0, 0);

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
}
void InfoBar::update(){}
void InfoBar::addScore(int points) {
	score += points;
}