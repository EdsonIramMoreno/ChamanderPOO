#ifndef _GameManagerC
#define _GameManagerC 
#include <iostream>
#include <Windows.h>
#include "Player.h"
#include "Object.h"
#include "Structure.h"
using namespace std;

enum MessageDisplay {
	Nothing, WINNER, LOSER, TASK_COMPLETED, DEAD_CHECKED, TIME_D_WIN, RESTART
};

class GameManagerC {
private:
	MessageDisplay Message;
	static GameManagerC* instance;
	GameManagerC() {

	}
	int DayManager = 0;
	int irainSprite = 0;
	bool Day = true;
	int iObj = 0;
	int timeDelay = 0;
	int rainTime = 0;
	bool move = true;
	bool rain = false;

	bool rainDuration() {
		if (rain == true) {
			if (rainTime < 90) {
				rainTime++;
				return true;
			}
			else {
				rainTime = 0;
				rain = false;
				return false;
			}
		}
		return false;
	}

	void isStartingtoRain() {
		if (Day == false && rain == false) {
			int aux = 0;
			srand(time(NULL));
			aux = 0 + rand() % (26);
			if (aux == 2) {
				rainTime = 0;
				rain = true;
			}
			else {
				rain = false;
			}
		}
	}

	void setirainSprite() {
		if (irainSprite < 13)
			irainSprite++;
		else
			irainSprite = 0;
	}

	bool isUnderWater(Player* player) {
		if (player->GetPosY() <= 20)
			return true;
		else
			return false;
	}

	bool DoNotMove(Player* player, int x, int z) {
		if ((player->GetPosX() < -370 && player->GetPosX() > -385) && (player->GetPosZ() < -60 && player->GetPosZ() > -135))
			return false;
		if ((player->GetPosX() < -370 && player->GetPosX() > -465) && (player->GetPosZ() < -120 && player->GetPosZ() > -135))
			return false;
		if ((player->GetPosX() < -450 && player->GetPosX() > -465) && (player->GetPosZ() < 35 && player->GetPosZ() > -135))
			return false;
		if ((player->GetPosX() < -370 && player->GetPosX() > -465) && (player->GetPosZ() < 35 && player->GetPosZ() > 20))
			return false;
		if ((player->GetPosX() < -370 && player->GetPosX() > -385) && (player->GetPosZ() < 35 && player->GetPosZ() > -35))
			return false;
		if (z >= -500 && x >= -500 && z <= 500 && x <= 500)
			return true;
		else return false;
		return true;
	}

	void setMov(bool move) {
		this->move = move;
	}

	void setiObj() {
		if (iObj < 1)
			iObj++;
		else
			iObj = 0;
	}

	void ChangeSkyIlumination(GLfloat Luz[4]) {
		int aux = DayManager;
		if (Day) {
			if (DayManager < 100 || DayManager >= 325 && DayManager < 400) {
				/*Luz[0] = 150;
				Luz[1] = 150;
				Luz[2] = 150;*/
				Luz[0] = 3.4;
				Luz[1] = 3.4;
				Luz[2] = 3.4;
			}
			else if (DayManager >= 100 && DayManager < 150 || DayManager >= 250 && DayManager < 325) {
				/*Luz[0] = 175;
				Luz[1] = 175;
				Luz[2] = 175;*/
				Luz[0] = 3.75;
				Luz[1] = 3.75;
				Luz[2] = 3.75;
			}
			else if (DayManager >= 150 && DayManager < 250) {
				Luz[0] = 4.1;
				Luz[1] = 4.1;
				Luz[2] = 4.1;//250
			}
		}
		else {
			if (DayManager < 100 || DayManager >= 280 && DayManager < 340) {
				Luz[0] = 2.8; //120
				Luz[1] = 2.8;
				Luz[2] = 2.8;
			}
			else if (DayManager >= 100 && DayManager < 150 || DayManager >= 225 && DayManager < 280) {
				Luz[0] = 2.25;//100
				Luz[1] = 2.25;
				Luz[2] = 2.25;
			}
			else if (DayManager >= 150 && DayManager < 225) {
				Luz[0] = 1.7;//50
				Luz[1] = 1.7;
				Luz[2] = 1.7;
			}
		}
	}
	
	
public:
	
	static GameManagerC* getInstance() {
		if (instance == NULL)
			instance = new GameManagerC();
		return instance;
	}

	bool RecolectRamita(Player *player, Object* Ramita, int distancia) {
		float auxX1, auxX2, auxZ1, auxZ2;
		auxX1 = Ramita->getX();
		auxX2 = Ramita->getX();
		auxZ1 = Ramita->getZ();
		auxZ2 = Ramita->getZ();
		auxX1 -= distancia;
		auxX2 += distancia;
		auxZ1 -= distancia;
		auxZ2 += distancia;
		if ((player->GetPosX() >= auxX1 && player->GetPosX() <= auxX2) && (player->GetPosZ() >= auxZ1 && player->GetPosZ() <= auxZ2)) {
			if (Ramita->getX() != -445 && (Ramita->getZ() != -60 || Ramita->getZ() != -57 || Ramita->getZ() != -54 || Ramita->getZ() != -51 || Ramita->getZ() != -48)) {
				return true;
			}
		}
		return false;
	}

	bool CrossRiver(Player* player) {
		if ((player->GetPosX() >= -20 && player->GetPosX() <= 180) && (player->GetPosZ() >= 120 && player->GetPosZ() <= 140)) {
			return true;
		}
		return false;
	}

	void reStartGameValues() {
		DayManager = 0;
		irainSprite = 0;
		Day = true;
		DayManager = 0;
		irainSprite = 0;
		timeDelay = 0;
		rainTime = 0;
		Day = true;
		rain = false;
		Message = Nothing;
	}

	int DaynNight(GLfloat Luz[4]) {
		ChangeSkyIlumination(Luz);
		DayManager++;
		if (Day == true) {
			if (DayManager > 400) {
				DayManager = 0;
				Day = false;
				return 1;
			}
			else return 0;
		}
		else{
			if (DayManager > 340) {
				DayManager = 0;
				Day = true;
				return 0;
			}
			else return 1;
		}
	}

	void ManageGame(Player** playerC, HWND hWnd, Object* Ramita[5], Structure* Estructura[10][2], Object* Porygon, Object* Marril, int x, int z) {
		for (short i = 0; i < 5; i++) {
			(*playerC)->setableToPickRamita(RecolectRamita((*playerC), Ramita[i], 10));
			if ((*playerC)->isableToPickRamita()) {
				Ramita[i]->setReachable(true);
				break;
			}
		}

		if (RecolectRamita((*playerC), Porygon, 20)) {
			Porygon->setReachable(true);
		}

		if (RecolectRamita((*playerC), Marril, 10)) {
			Marril->setReachable(true);
		}

		(*playerC)->damage(isUnderWater((*playerC)),rain, isInsideStructure((*playerC), Estructura));

		(*playerC)->setiFlamita();

		if (rainDuration())
			setirainSprite();
		else
			isStartingtoRain();

		(*playerC)->SetiChar();

		if (Message != DEAD_CHECKED) {
			if ((*playerC)->isdead())
				Message = LOSER;
		}

		if (Message == WINNER) {
			timeDelay++;
			if (timeDelay == 50) {
				Message = TIME_D_WIN;
			}
		}

		setMov(DoNotMove((*playerC), x, z));

		if(DayManager % 3 == 0)
		setiObj();
	}

	int getRainSprite() {
		return irainSprite;
	}

	bool getMov() {
		return move;
	}

	bool isInsideStructure(Player* playerC, Structure* Estructura[10][2]) {
		if (rain == true) {
			for (int i = 0; i < 10; i++) {
				int posPx = playerC->GetPosX();
				int posEx = Estructura[i][0]->getx();
				int posEx2 = Estructura[i][0]->getx2();
				int posPz = playerC->GetPosZ();
				int posEz = Estructura[i][0]->getz();
				int posEz2 = Estructura[i][0]->getz2();
				if (playerC->GetPosX() > Estructura[i][0]->getx() && playerC->GetPosX() < Estructura[i][0]->getx2()) {
					if (playerC->GetPosZ() < Estructura[i][0]->getz() && playerC->GetPosZ() > Estructura[i][0]->getz2()) {
						Estructura[0][i]->setReachable(true);
						return true;
					}
				}
				/*else
					Estructura[i]->Reachable = false;*/
			}
			return false;
		}
		else return false;
	}

	int getiObj() {
		return iObj;
	}

	void setMessage(MessageDisplay m) {
		this->Message = m;
	}

	int getMessage() {
		return this->Message;
	}

	bool isRaining() {
		return rain;
	}

};
GameManagerC* GameManagerC::instance = NULL;

#endif