#include "SceneObject.h"

SceneObject::SceneObject(Game* _game, Point2D<int> _pos, int _lives, int _width, int _height) : GameObject(_game), pos(_pos), lives(_lives), width(_width), height(_height){}



void SceneObject::hit(SDL_Rect attackRect, bool src) { //es el comprobante del hit de los objetos (attackRect es el del atacante)
	
	SDL_Rect enemy = { pos.getX(), pos.getY(), width, height }; //creacion del rect del objeto
	if (SDL_HasIntersection(&attackRect, &enemy)) { //choque
		lives--;
	}
	
	
}