#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "PlayState.h"


const int DELTA_TIME = 16;
const int SPEED_INCREMENT = 50;
const int VERTICAL_OFFSET = 25;
const int ALIEN_SPEED = 10;


class Game;
enum MovingStates {
	Moving,
	goDown
};
class Mothership : public GameObject
{
protected:
	int alienCont = 0;
	int timeCounter = 0;
	int timeToMove = 1000;
	bool shouldmove = false;
	bool canMove = true;
	bool landed = false;
	Vector2D<int>aliensDirection = { 1,0 };
	
	MovingStates state = Moving;
public:
	Mothership(Game* _game);
	void update()override;
	void render() const override;
	void save(std::ostream& os) const override;
	void addAlien();
	//Retorna la direccion de los aliens 
	Vector2D<int> getDirection() const { return aliensDirection; }
	// Lleva el contador de tiempo para cada actualizacion e 

	//indicar cual es el frame en el que los aliens se deben mover
	bool shouldMove();

	//Cambia direccion si se indica
	void cannotMove();

	MovingStates getState() { return state; }
	int getVerticalOffset();
	int getAlienSpeed() { return ALIEN_SPEED; }
	void alienDied();
	void alienLanded();
	bool haveLanded() { return landed; }
	int getCont() const { return alienCont; }
};



//#pragma once
//#include "GameObject.h"
//#include "Vector2D.h"
//#include <iostream>
//enum MovementState {
//	MOVE_LEFT,
//	MOVE_RIGHT
//};
//class Mothership : public GameObject
//{
//private:
//	int time = 0;
//	MovementState state;
//	int level;
//	int remaingTime = 100;
//	bool dontChange = false;;
//	Vector2D<double> direction = { 1.2,0 };
//public:
//	Mothership(Game* game);
//
//	Vector2D<double> getDirection() const;
//	MovementState getState();
//	MovementState setDirection(MovementState newstate);
//	bool shouldMove();
//	
//	void cannotMove();
//	
//	void alienLanded();
//	bool haveLanded();
//	
//	void render() const override;
//	void update() override;
//	void save(ostream& os) const override;
//};
//
