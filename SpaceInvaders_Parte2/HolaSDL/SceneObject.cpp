#include "SceneObject.h"

SceneObject::SceneObject(Game* _game, Point2D<int> _pos, int _lifes, int _width, int _height) : GameObject(_game), pos(_pos), lifes(_lifes), width(_width), height(_height){}


void SceneObject::setListIterator(std::list<SceneObject*>::iterator iterator) {
	listIterator = iterator;
}
//Comprueba colision y resta la vida pertinente 
void SceneObject::hit(SDL_Rect attackRect, char src) { 

	SDL_Rect objectRect = { pos.getX(), pos.getY(), width, height }; 

<<<<<<< HEAD
	if (SDL_HasIntersection(&attackRect, &objectRect))  lifes--;
=======
	/*----------------------
	PROBABLEMENTE ESTA MAL, NO SE COMPRUEBA CON SRC

	PROBABLEMENTE CON SRC SE EVALUE EN CADA UNA DE LAS LLAMDAS DE HIT DE LOS DISTINTOS OBJECTS
	-------------------------*/
	if (SDL_HasIntersection(&attackRect, &objectRect)) 
		lifes--;
>>>>>>> parent of d00c28f (render hechisimo ;P)
}