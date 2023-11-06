#pragma once

#include "Vector2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Bunker.h"
#include "Alien.h"
#include "Cannon.h"
#include "checkML.h"

using namespace std;

const Uint32 LASER_WIDTH = 5;
const Uint32 LASER_HEIGHT = 30;
const Vector2D<int> LASER_SPEED(0, 1);
class Game;
class Laser
{
private:
	Point2D<int> pos;
	Game* game;
	bool src; //true -> alien | false->cannon
	SDL_Renderer* renderer;
	SDL_Rect* rect;
	bool canSelfDestroy;
public:
	Laser(Point2D<int>& pos, bool src, SDL_Renderer* renderer, Game* game);
	struct color {
		int r;
		int g;
		int b;
		int alpha;
	};
	void render();
	bool update(const vector<Alien*>& aliens, const vector<Bunker*>& bunkers,
		const vector<Laser*>& lasers, Cannon* cannon);
	bool bunkerColision( const vector<Bunker*>& bunkers);
	bool laserColision(const vector<Laser*>& lasers, bool srcOpposite);
	bool alienColision(const vector<Alien*>& aliens);
	bool cannonColision(Cannon* cannon);
	SDL_Rect* getRect();
	bool getSource();
	void setSelfDestroy();

};

