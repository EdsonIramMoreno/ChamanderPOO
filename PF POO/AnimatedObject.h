#ifndef _AnimatedObject
#define _AnimatedObject

#include "Object.h"
#include <iostream>
using namespace std;

class AnimatedObject : public Object {
	bool straight = false, forward = true, turnleft = false;
	float movx, movz, rotation;
public:
	AnimatedObject(string obj, string texture, bool mode, float x, float y, float z) : Object(obj,texture,mode) {
		this->setX(x);
		this->setY(y);
		this->setZ(z);
		movx = x;
		movz = z;
		rotation = 0;
	}

	void BoxAnimation() {
		if (straight) {
			if (forward) {
				float aux = getZ() + 100;
				if (movz < aux) {
					movz++;
				}
				else {
					forward = false;
					straight = false;
					turnleft = false;
					rotation = 180;
				}
			}
			else {
				if (movz > getZ()) {
					movz--;
				}
				else {
					forward = true;
					straight = false;
					turnleft = true;
					rotation = 0;
				}
			}
		}
		else {
			if (turnleft) {
				float aux = getX() + 50;
				if (movx < aux) {
					movx++;
				}
				else {
					straight = true;
					rotation = 270;
				}
			}
			else {
				if (movx > getX()) {
					movx--;
				}
				else {
					straight = true;
					rotation = 90;
				}
			}
		}
	}

	void EscapeAnimation(char EscapeDir) {
		switch (EscapeDir) {
		case 'x': {
			if (!straight) {
				if (movx < 470) {
					if (movx < getX() + 10) {
						movx++;
					}
					else {
						setX(movx);
						setReachable(false);
						
					}
				}
				else {
					straight = true;
					setRotation(180);
				}
			}
			else {
				if (movx > -470) {
					if (movx > getX() - 10) {
						movx--;
					}
					else {
						setX(movx);
						setReachable(false);
					}
				}
				else {
					setRotation(0);
					straight = false;
				}
			}
		}
			break;
		case 'z': {
			if (!straight) {
				if (movz < 470) {
					if (movz < getZ() + 10) {
						movz++;
					}
					else {
						setZ(movz);						
						setReachable(false);						
					}
				}
				else {
					setRotation(90);
					straight = true;
				}
			}
			else {
				if (movz > -470) {
					if (movz > getZ() - 10) {
						movz--;
					}
					else {
						setZ(movz);						
						setReachable(false);						
					}
				}
				else {
					straight = false;
					setRotation(270);
				}
			}
		}
				break;
		}
	}

	float getMovX() {
		return movx;
	}

	float getMovZ() {
		return movz;
	}

	float getRotation() {
		return rotation;
	}

	void setRotation(int Rot) {
		this->rotation = Rot;
	}
};
#endif
