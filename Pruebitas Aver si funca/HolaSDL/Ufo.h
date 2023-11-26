#pragma once
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"

const int UFO_SPEED = 3;

class Game;
class Ufo : public SceneObject
{
private:
	enum States {
		HIDE,
		SHOWN,
		DEAD
	};
	Vector2D<int> direction = { 1,0 };
	States state = HIDE;
	Texture* texture;
	int randomShownTime;
	SDL_Rect* rect;
	int timeCont = 0;
public:
	Ufo(Game* _game, Point2D<int>_pos, Texture* _texture, int _randomShownTime);
	~Ufo();

	void update()override;
	void render() const override;
};

