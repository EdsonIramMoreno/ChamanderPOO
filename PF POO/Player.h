//Regresar a que se vea charmander

#ifndef _Player
#define _Player
#include "Model.h"

class Player{
	int health;
	int Ramitas;
	int iCharmander;
	int iCharState;
	int iFlamita;
	bool ableToPickRamita;
	bool dead;
	GLdouble PosX, PosY, PosZ;
public:
	//short rotacion;
	EDXFramework::Model* Charmander[2][4];
	//Model* Char;// = new Model("Modelos//Charmander//Charmander0.obj", "Modelos//Charmander//Charmander.bmp", 1);

	Player();
	/*Player();*/

	~Player();

	void setCharmanderPos(GLdouble x, GLdouble y, GLdouble z);

	GLdouble GetPosX();

	GLdouble GetPosY();

	GLdouble GetPosZ();

	int GetiChar();

	void SetiChar();

	void SetStateChar(int);

	int GetStateChar();

	void incTRamas();

	void damage(bool, bool, bool);

	void setableToPickRamita(bool);

	bool isableToPickRamita();

	int getRamitas();

	int getiFlamita();

	void setiFlamita();

	void reStartPlayerValues();

	int getHealth();

	bool isdead();

	/*void playerInitialize();

	void playerUpdate();

	void playerMove(char movDir);

	void playerturnRight();

	void playerturnLeft();

	void  playerturnUp();

	void playerturnDown();*/

};

#endif // !1