#pragma once
#include "SceneObject.h"

#include "texture.h"
#include "Vector2D.h"

const int UFO_SPEED = 2;
const int DEAD_FRAMES = 70;
const int UFO_POINTS = 100;
class PlayState;
class Game;
class Ufo : public SceneObject
{
private:
	enum States {
		HIDE,
		SHOWN,
		DEAD
	};
	Vector2D<int> direction = { -1,0 };
	States state;
	Texture* texture;
	int randomShownTime;
	int deadFramesCont = 0;
	std::unique_ptr<SDL_Rect> rect;
	int timeCont = 0;
	Point2D<int> initialPos;
	//Comprueba si ha llegado al limite de la pantalla y cambia la direccion
	void checkLimits();
	//randomiza el cambio de estado de SHOWN a HIDE y viceversa
	void canShow();
public:
	Ufo(PlayState* playState, std::istream& entrada, Texture* _texture);

	void update()override;
	void render() const override;
	void save(std::ostream& os) const  override;
	bool hit(SDL_Rect* otherRect, char otherSrc) override;
};

