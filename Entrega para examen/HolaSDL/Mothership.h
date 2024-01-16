#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "PlayState.h"


const int SPEED_INCREMENT = 2;
const int VERTICAL_OFFSET = 10;
const int TIME_TO_MOVE = 1000;
const int ALIEN_SPEED = 10;


class Game;
class Mothership : public GameObject
{
protected:
	int alienCont = 0;
	int timeCounter = SDL_GetTicks();
	bool shouldmove = false;
	bool jump = false;
	bool landed = false;
	Vector2D<int>moveDirection = { ALIEN_SPEED ,0 };
	Vector2D<int>jumpVector = { 0 , VERTICAL_OFFSET };
	Vector2D<int> currentDirection;
	bool changeDirection = false;

public:
	Mothership(Game* _game);
	void update()override;
	void render() const override;
	void save(std::ostream& os) const override;
	void addAlien();
	//Retorna la direccion de los aliens 
	Vector2D<int> getDirection() const { return currentDirection; }
	// Lleva el contador de tiempo para cada actualizacion e 

	//indicar cual es el frame en el que los aliens se deben mover
	bool shouldMove();

	//Cambia direccion si se indica
	void cannotMove();

	void alienDied();
	void alienLanded();
	bool haveLanded() { return landed; }
	int getCont() const { return alienCont; }
};
