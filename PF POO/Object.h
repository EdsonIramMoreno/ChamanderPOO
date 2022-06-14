#ifndef _Object
#define _Object
#include "Model.h"
#include <stdlib.h>
#include <Time.h>

using namespace EDXFramework;

class Object : public  Model{
	float x = 0, y = 0, z = 0;
	bool Reachable;
public:
	
	Object(string obj, string texture, bool mode) : Model(obj, texture, mode){
		this->Reachable = false;
	}

	Object(string obj, string texture, bool mode,int x, int z, float y) : Model(obj, texture, mode) {
		int auxRan = -10 + rand() % (11 - (-10));
		this->y = y;
		this->x = x - auxRan;
		this->z = z - auxRan;
	}

	void SetRamitasRandom(Object* Ramita[], Object* Trees[], int cant) {
		int arr[5] = { -1,-1,-1,-1,-1 };
		int aux;
		short j = 0;
		while (j < 5) {
			bool checar = true;
			srand(time(NULL));
			aux = 0 + rand() % (cant);
			for (short i = 0; i < 5; i++) {
				if (aux == arr[i]) {
					checar = false;
					break;
				}
			}
			if (checar) {
				Ramita[j] = new Object("Modelos//Ramita//RamaPro.obj", "Modelos//Ramita//TexturaRama.bmp", 1, Trees[aux]->getX(), Trees[aux]->getZ(), 0);
				arr[j] = aux;
				j++;
			}
		}
	}

	void setY(float y) {
		this->y = y;
	}

	void setX(float x) {
		this->x = x;
	}

	void setZ(float z) {
		this->z = z;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float getZ() {
		return z;
	}

	bool isReachable() {
		return this->Reachable;
	}

	void setReachable(bool Reachable) {
		this->Reachable = Reachable;
	}

	virtual void BoxAnimation() {
		this->x = x;
	}

	virtual void EscapeAnimation(char Escape) {

	}

	virtual float getMovX() {
		return this-> x;
	}

	virtual float getMovZ() {
		return this->z;
	}

	virtual float getRotation() {
		return 0;
	}

	virtual void setRotation(float rot) {
		
	}

	/*void SetRandomPosition(Object*Ob, Object* Objetos[], int cant) {
		Reachable = false;
		bool checar = true;
		int auxX = 0, auxZ = 0;
		while (checar) {
			srand(time(NULL));
			auxX = -499 + rand() % (500 - (-499));
			auxZ = -499 + rand() % (500 - (-499));
			if (auxX < 228 && auxZ < -140 || auxX > 430 && auxZ > 50) {
				for (short i = 0; i < cant; i++) {
					if (auxX == Objetos[i]->getx() && auxZ == Objetos[i]->getz()) {
						checar = false;
						break;
					}
				}
				if (checar) {
					Ob->setX(auxX);
					Ob->setZ(auxZ);
					break;
				}
				else
					checar = true;
			}
		}
	}*/
};

#endif