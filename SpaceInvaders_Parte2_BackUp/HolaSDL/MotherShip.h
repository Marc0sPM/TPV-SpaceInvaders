#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"
class Game;

int ALIEN_VERTICAL_SHIFT = 0;
const Uint32 ALIEN_INCREMENT_SPEED = 5;

class MotherShip : public GameObject
{

protected:
	Uint32 timeCounter = 0;
	Uint32 timeToMove = 1000;
	Vector2D<int> aliensDirection = { 1, 0 };
	bool cantMove = false; //indica cuando no se puede mover porque ha llegado al extremo de la pantalla
	bool landed = false;
	int alienCont;
public:
	MotherShip(Game* _game,int alienCont);
	~MotherShip();

	Vector2D<int> getDirection() const { return aliensDirection; }
	//Lleva el contador de tiempo para cada actualizacion y 
	bool shouldMove();
	//Evalua cuando los aliens se chocan contra la pared y si se puede cambiar la direccion
	void cannotMove(); //no se si es bool
	//Disminuye en uno el contador de aliens
	void alienDied();
	//informa a la mothership de que un alien ha aterrizado
	void alienLanded();
	//Comprueba si al menos un alien ha llegado a la posicion del cannon
	bool haveLanded() { return landed; }
	//Devuelve el contador de aliens
	int getAlienCount() const { return alienCont; }

	void render()const override;
	void update() override;
	//void save(ostream& os) const override;  COMPLETAR MAS TARDE
	 
};

