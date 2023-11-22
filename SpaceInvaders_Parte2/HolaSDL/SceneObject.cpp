#include "SceneObject.h"

SceneObject::SceneObject(Game* _game, Point2D<int> _pos, int _lives, int _width, int _height) : GameObject(_game), pos(_pos), lives(_lives), width(_width), height(_height){}



void SceneObject::hit(SDL_Rect attackRect, char src) { 
	//Comprueba colision y resta la vida pertinente 
	
	SDL_Rect objectRect = { pos.getX(), pos.getY(), width, height }; 

	/*----------------------
	PROBABLEMENTE ESTA MAL, NO SE COMPRUEBA CON SRC

	PROBABLEMENTE CON SRC SE EVALUE EN CADA UNA DE LAS LLAMDAS DE HIT DE LOS DISTINTOS OBJECTS
	-------------------------*/
	if (SDL_HasIntersection(&attackRect, &objectRect)) 
		lives--;
}