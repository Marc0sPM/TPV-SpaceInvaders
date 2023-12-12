#pragma once
#include "checkML.h"
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"

const int UFO_SPEED = 2;
const int DEAD_FRAMES = 70;
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
	SDL_Rect* rect;
	int timeCont = 0;
	Point2D<int> initialPos;
	//Comprueba si ha llegado al limite de la pantalla y cambia la direccion
	void checkLimits();
	//randomiza el cambio de estado de SHOWN a HIDE y viceversa
	void canShow();
public:
	Ufo(Game* _game, Point2D<int>_pos, Texture* _texture, int _randomShownTime,int _state);
	~Ufo();

	void update()override;
	void render() const override;
	void save(std::ostream& os) const  override;
	bool hit(SDL_Rect* otherRect, char otherSrc) override;
};
