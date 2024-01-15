#pragma once

#include "Vector2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Bunker.h"
#include "Alien.h"
#include "Cannon.h"
#include "SceneObject.h"
#include <istream>


using namespace std;

const Uint32 LASER_WIDTH = 5;
const Uint32 LASER_HEIGHT = 30;
const Vector2D<int> LASER_SPEED(0, 1);
class Game;
class PlayState;
class Laser : public SceneObject
{
private:
	char src; //b -> alien | r->cannon
	SDL_Renderer* renderer;
	std::unique_ptr<SDL_Rect> rect;
	struct color {
		int r;
		int g;
		int b;
		int alpha;
	};
public:
	//Por lectura
	Laser(PlayState* playState, std::istream& entrada);
	//Disparado
	Laser(PlayState* playState, Point2D<int>& _pos, char _src);
	void render() const override;
	void update() override;

	SDL_Rect* getRect()const { return rect.get(); }
	bool getSource() const { return src; }

	bool hit(SDL_Rect* otherRect, char src)override;
	void save(std::ostream& os) const override;

};

