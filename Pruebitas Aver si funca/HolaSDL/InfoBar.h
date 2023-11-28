#pragma once
#include "GameObject.h"
#include "texture.h"
#include "Cannon.h"
#include "Vector2D.h"

const int LIFES_OFFSET = 10;
class Game;
class InfoBar : public GameObject
{
private: 
	int score;
	Texture* pointsTexture;
	Texture* lifesTexture;
	Point2D<int> posLifes;
	Point2D<int> posScore;
	SDL_Rect* destRectLifes;
	SDL_Rect* rectScore;
	Cannon* cannon;
public:
	InfoBar(Game* _game, Texture* _texturePoints, Texture* _textureLifes,
		Cannon* _cannon, int score);
	~InfoBar();
	void update()override;
	void render()const override;
	
};

