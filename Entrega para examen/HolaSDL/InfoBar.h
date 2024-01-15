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

	std::unique_ptr<SDL_Rect> rectLifes;
	std::unique_ptr<SDL_Rect> rectScore;
	Cannon* cannon;
	void setRects();
public:
	InfoBar(Game* _game, std::istream& entrada, Texture* _texturePoints, Texture* _textureLifes,
		Cannon* _cannon);
	void update()override;
	void render()const override;
	void save(std::ostream& os)const  override;
	void addScore(int points);
};

