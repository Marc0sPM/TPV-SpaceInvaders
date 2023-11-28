#include "checkML.h"
#include "Exceptions.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include <iostream>

using namespace std;

using uint = unsigned int;



int main(int argc, char* argv[])
{
	try {
		Game game;
		game.run();
	}
	catch (const InvadersError& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
