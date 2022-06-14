#ifndef _Structure
#define _Structure
#include <iostream>
#include"Object.h"

using namespace std;

class Structure : public Object {
	int cx2, cz2, posx, posz;
public:
	Structure(string obj, string texture, bool mode, int x1, int z1, int x2, int z2,
		int y, int posx, int posz) : Object (obj, texture, mode) {
		this->setX(x1);		this->setZ(z1);		this->setY(y);
		this->cx2 = x2;		this->cz2 = z2;
		this->posx = posx;	this->posz = posz;
	}
	int getposx() {
		return this->posx;
	}
	int getx() {
		return this->getX();
	}
	int getx2() {
		return this->cx2;
	}
	int getposz() {
		return this->posz;
	}
	int getz() {
		return this->getZ();
	}
	int getz2() {
		return this->cz2;
	}
	int gety() {
		return this->getY();
	}

	class builder{
		string obj, texture;
		bool mode;
		int x1, x2, z1, z2, y, posx, posz;
	public:
		Structure* build() {
			return new Structure(obj, texture, mode, x1, z1, x2, z2, y, posx, posz);
		}

		builder* Obj(string obj) {
			this->obj = obj;
			return this;
		}
		builder* Texture(string texture) {
			this->texture = texture;
			return this;
		}
		builder* Mode(bool mode) {
			this->mode = mode;
			return this;
		}
		builder* Ex1(int x1) {
			this->x1 = x1;
			return this;
		}
		builder* Ex2(int x2) {
			this->x2 = x2;
			return this;
		}
		builder* Ez1(int z1) {
			this->z1 = z1;
			return this;
		}
		builder* Ez2(int z2) {
			this->z2 = z2;
			return this;
		}
		builder* sy(int y) {
			this->y = y;
			return this;
		}
		builder* Posx(int posx) {
			this->posx = posx;
			return this;
		}
		builder* Posz(int posz) {
			this->posz = posz;
			return this;
		}
	};
};

#endif
