#include "Player.h"


using namespace std;

Player::Player(){
	this->Ramitas = 0;
	this->iCharmander = 0;
	this->health = 100;
	this->iCharState = 0;
	this->iFlamita = 0;
	this->dead = false;
}

Player::~Player() {
	delete this->Charmander[0][0];
	delete this->Charmander[0][1];
	delete this->Charmander[0][2];
	delete this->Charmander[0][3];
	delete this->Charmander[1][0];
	delete this->Charmander[1][1];
	delete this->Charmander[1][2];
	delete this->Charmander[1][3];
}

void Player::setCharmanderPos(GLdouble x, GLdouble y, GLdouble z) {
	this->PosX = x;
	this->PosY = y;
	this->PosZ = z;
}

GLdouble Player::GetPosX() {
	return this->PosX;
}

int Player::getHealth() {
	return this->health;
}

GLdouble Player::GetPosY() {
	return this->PosY;
}

GLdouble Player::GetPosZ() {
	return this->PosZ;
}

int Player::GetiChar() {
	if (this->iCharState == 1)
		return this->iCharmander;
	else
		return this->iCharmander;
}

void Player::SetiChar() {
	if (iCharmander < 3) {
		iCharmander++;
	}
	else
		iCharmander = 0;
}

void Player::SetStateChar(int state) {
	if (state != this->iCharState) {
		this->iCharmander = 0;
		if (state == 0 || state == 1) {
			this->iCharState = state;
		}
		else
			this->iCharState = 1;
	}
}

int Player::GetStateChar() {
	return this->iCharState;
}

void Player::incTRamas() {
	if (this->ableToPickRamita) {
		if (this->Ramitas < 6)
			this->Ramitas++;
	}
}

void Player::reStartPlayerValues() {
	this->Ramitas = 0;
	this->iCharmander = 0;
	this->health = 100;
	this->iCharState = 0;
	this->iFlamita = 0;
	this->dead = false;
}

void Player::damage(bool damage, bool rain, bool isInside) {
	if (damage) {
		if (this->health > 0)
			this->health--;
		else this->dead = true;
	}
	else if (rain) {
		if (!isInside) {
			if (this->health > 0)
				this->health--;
			else this->dead = true;
		}
		else if (this->health < 100 && this->health != 0)
			this->health++;
		else if (this->health == 0)
			this->dead = true;
	}
	else {
		if (this->health < 100 && this->health != 0)
			this->health++;
		else if (this->health == 0)
			this->dead = true;
	}
}

void Player::setableToPickRamita(bool able) {
	this->ableToPickRamita = able;
}

bool Player::isableToPickRamita() {
	return this->ableToPickRamita;
}

int Player::getRamitas() {
	return this->Ramitas;
}

int Player::getiFlamita() {
	return this->iFlamita;
}

void Player::setiFlamita() {
	if (this->iFlamita < 3) {
		this->iFlamita++;
	}
	else {
		this->iFlamita = 0;
	}
}

bool Player::isdead() {
	return this->dead;
}