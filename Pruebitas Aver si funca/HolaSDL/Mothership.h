#pragma once
#include "GameObject.h"
#include "checkML.h"
#include "Vector2D.h"


const int DELTA_TIME = 16;
const int SPEED_INCREMENT = 75;
const int VERTICAL_OFFSET = 25;


class Game;
enum MovingStates {
	Moving,
	goDown
};
class Mothership : public GameObject
{
protected:
	int alienCont;
	int timeCounter = 0;
	int timeToMove = 1000;
	bool shouldmove = false;
	bool canMove = true;
	Vector2D<int>aliensDirection = { 1,0 };
	MovingStates state = Moving;
	int ALIEN_SPEED = 10;
public: 
	Mothership(Game* _game);
	void update()override;
	void render() const override;
	void addAlien();
	//Retorna la direccion de los aliens 
	Vector2D<int> getDirection() const { return aliensDirection; }
	// Lleva el contador de tiempo para cada actualizacion e 
	
	//indicar cual es el frame en el que los aliens se deben mover
	bool shouldMove();

	//Cambia direccion si se indica
	void cannotMove();

	MovingStates getState() { return state; }
	void setState(MovingStates _state);
	
	int getVerticalOffset();
	int getAlienSpeed() { return ALIEN_SPEED; }
};

