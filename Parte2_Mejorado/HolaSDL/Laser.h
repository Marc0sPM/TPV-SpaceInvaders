#pragma once

#include "Vector2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Bunker.h"
#include "Alien.h"
#include "Cannon.h"
#include "checkML.h"
#include "SceneObject.h"
#include <istream>

using namespace std;

const Uint32 LASER_WIDTH = 5;
const Uint32 LASER_HEIGHT = 30;
const Vector2D<int> LASER_SPEED(0, 1);
class Game;
class Laser : public SceneObject
{
private:

	char src; //b -> alien | r->cannon
	SDL_Renderer* renderer;
	SDL_Rect* rect;
public:
	Laser(Point2D<int>& pos, char src, Game* game);
	struct color {
		int r;
		int g;
		int b;
		int alpha;
	};
	void render() const override;
	void update() override;

	SDL_Rect* getRect()const { return rect; }
	bool getSource() const { return src; }

	bool hit(SDL_Rect* otherRect, char src)override;
	void save(std::ostream& os) const override;

};

