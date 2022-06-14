#ifndef __Escena
#define __Escena

#include <gl\GLU.h>
#include <gl\GL.h>
#include <string.h>
#include <strsafe.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "Model.h"
#include "Water.h"
#include "Billboard.h"
#include "Fog.h"
#include "Camera.h"
#include "Player.h"
#include <thread>
#include <vector>
#include "Object.h"
#include "GameManagerC.h"
#include "Structure.h"
#include "AnimatedObject.h"

using namespace std;

//void CargarTerreno(Terrain** Ter, HWND hWnd);

#define BILLSIZE 50

//BIENVENIDO AL ARCHIVO MAS IMPORTANTE DE TU PROYECTO
int iChar = 0;
class Scene : public Camera{
public:

	HWND hWnd = 0;

	short int skyIndex, lightIndex;
	float skyRotation;

	SkyDome* skyDome[2];
	Terrain *terrain = new Terrain(hWnd, L"Imagenes//Mapas.jpg", L"Imagenes//TerrenoTextura.jpg", L"Imagenes//TerrenoTextura.jpg", 1024, 1024);
	Water* lago = new Water(hWnd, L"Imagenes//Mapas.jpg", L"Imagenes//WaterTexture.jpg", 2112, 2112);
		//(HWND hWnd, WCHAR alturas[], WCHAR textura[], float ancho, float prof)
	GLfloat AmbMat[4] = { 5, 5, 5, 1 };
	Object* Ramita[5];
	Object* Trees[10];
	Object* TableNPB, * MiniMerry[2], * MiniMerry2[2],* Rock[4],* Porygon[2];
	Structure* Estructuras[10][2];
	AnimatedObject* Marril[2],* Meltan[2];
	EDXFramework::Model* Muelle;
	Billboard *billRain[14];
	Billboard* flama[4];
	Billboard* woodFire[4];
	/*static int loadModel(EDXFramework::Model* Charmander) {
		Charmander = new EDXFramework::Model("Modelos//Arma//Cyborg_Riffle.obj", "Modelos//Arma//Cyborg_Riffle_D.bmp", 1);
		return 1;
	}*/

	Scene(HWND hWnd, Player *player){
		this->hWnd = hWnd;
		skyIndex = lightIndex, skyRotation = 0;
		GLfloat AmbPos[] = { 0, 400, 400, 1 };


		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, AmbPos);

		Muelle = new EDXFramework::Model("Modelos//Muelle//MuelleWood.obj", "Modelos//Muelle//WoodMuelleA.bmp", 1);
		//Objetos con clases
		Estructuras[0][0] = Structure::builder().Obj("Modelos//CentroPokemon//Centro1.obj")->
			Texture("Modelos//CentroPokemon//CentroPokemonTextrue1.bmp")->Mode(1)->
			Ex1(-460)->Ez1(25)->Ex2(-380)->Ez2(-130)->sy(37)->Posx(-420)->Posz(-50)->build();
		Estructuras[0][1] = Structure::builder().Obj("Modelos//CentroPokemon//Centro1.obj")->
			Texture("Modelos//CentroPokemon//CentroPokemonTextrue1.bmp")->Mode(1)->
			Ex1(-460)->Ez1(25)->Ex2(-380)->Ez2(-130)->sy(37)->Posx(-420)->Posz(-50)->build();
		Estructuras[1][0] = Structure::builder().Obj("Modelos//Hojas//Hojas.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-300)->Ez1(150)->Ex2(-280)->
			Ez2(115)->sy(terrain->Superficie(-280,130)*3+10)->Posx(-280)->Posz(130)->build();
		Estructuras[1][1] = Structure::builder().Obj("Modelos//Hojas//Hojas2.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-300)->Ez1(150)->Ex2(-280)->
			Ez2(115)->sy(terrain->Superficie(-280, 130) * 3 + 10)->Posx(-280)->Posz(130)->build();
		Estructuras[2][0] = Structure::builder().Obj("Modelos//Hojas//Hojas.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-20)->Ez1(-110)->Ex2(0)->
			Ez2(-145)->sy(terrain->Superficie(0, -130) * 3 + 10)->Posx(0)->Posz(-130)->build();
		Estructuras[2][1] = Structure::builder().Obj("Modelos//Hojas//Hojas2.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-20)->Ez1(-110)->Ex2(0)->
			Ez2(-145)->sy(terrain->Superficie(0, -130) * 3 + 10)->Posx(0)->Posz(-130)->build();
		Estructuras[3][0] = Structure::builder().Obj("Modelos//Hojas//Hojas.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(60)->Ez1(-410)->Ex2(80)->
			Ez2(-445)->sy(terrain->Superficie(80, -430) * 3 + 10)->Posx(80)->Posz(-430)->build();
		Estructuras[3][1] = Structure::builder().Obj("Modelos//Hojas//Hojas2.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(60)->Ez1(-410)->Ex2(80)->
			Ez2(-445)->sy(terrain->Superficie(80, -430) * 3 + 10)->Posx(80)->Posz(-430)->build();
		Estructuras[4][0] = Structure::builder().Obj("Modelos//Hojas//Hojas.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(420)->Ez1(340)->Ex2(440)->
			Ez2(305)->sy(terrain->Superficie(440, 320) * 3 + 10)->Posx(440)->Posz(320)->build();
		Estructuras[4][1] = Structure::builder().Obj("Modelos//Hojas//Hojas2.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(420)->Ez1(340)->Ex2(440)->
			Ez2(305)->sy(terrain->Superficie(440, 320) * 3 + 10)->Posx(440)->Posz(320)->build();
		Estructuras[5][0] = Structure::builder().Obj("Modelos//Hojas//Hojas.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(220)->Ez1(320)->Ex2(240)->
			Ez2(285)->sy(terrain->Superficie(240, 300) * 3 + 10)->Posx(240)->Posz(300)->build();
		Estructuras[5][1] = Structure::builder().Obj("Modelos//Hojas//Hojas2.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(220)->Ez1(320)->Ex2(240)->
			Ez2(285)->sy(terrain->Superficie(240, 300) * 3 + 10)->Posx(240)->Posz(300)->build();
		Estructuras[6][0] = Structure::builder().Obj("Modelos//Hojas//Hojas.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(410)->Ez1(50)->Ex2(430)->
			Ez2(15)->sy(terrain->Superficie(430, 30) * 3 + 10)->Posx(430)->Posz(30)->build();
		Estructuras[6][1] = Structure::builder().Obj("Modelos//Hojas//Hojas2.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(410)->Ez1(50)->Ex2(430)->
			Ez2(15)->sy(terrain->Superficie(430, 30) * 3 + 10)->Posx(430)->Posz(30)->build();
		Estructuras[7][0] = Structure::builder().Obj("Modelos//Hojas//Hojas.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-330)->Ez1(390)->Ex2(-310)->
			Ez2(355)->sy(terrain->Superficie(-310, 370) * 3 + 10)->Posx(-310)->Posz(370)->build();
		Estructuras[7][1] = Structure::builder().Obj("Modelos//Hojas//Hojas2.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-330)->Ez1(390)->Ex2(-310)->
			Ez2(355)->sy(terrain->Superficie(-310, 370) * 3 + 10)->Posx(-310)->Posz(370)->build();
		Estructuras[8][0] = Structure::builder().Obj("Modelos//Hojas//Hojas.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-200)->Ez1(-130)->Ex2(-180)->
			Ez2(-165)->sy(terrain->Superficie(-180, -150) * 3 + 10)->Posx(-180)->Posz(-150)->build();
		Estructuras[8][1] = Structure::builder().Obj("Modelos//Hojas//Hojas2.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-200)->Ez1(-130)->Ex2(-180)->
			Ez2(-165)->sy(terrain->Superficie(-180, -150) * 3 + 10)->Posx(-180)->Posz(-150)->build();
		Estructuras[9][0] = Structure::builder().Obj("Modelos//Hojas//Hojas.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-110)->Ez1(200)->Ex2(-90)->
			Ez2(165)->sy(terrain->Superficie(-90, 180) * 3 + 10)->Posx(-90)->Posz(180)->build();
		Estructuras[9][1] = Structure::builder().Obj("Modelos//Hojas//Hojas2.obj")->
			Texture("Modelos//Hojas//Hoja.bmp")->Mode(1)->Ex1(-110)->Ez1(200)->Ex2(-90)->
			Ez2(165)->sy(terrain->Superficie(-90, 180) * 3 + 10)->Posx(-90)->Posz(180)->build();
	
		skyDome[0] = new SkyDome(hWnd, 14, 14, 1000, L"Imagenes//SkyDomeDay.jpg");
		skyDome[1] = new SkyDome(hWnd, 14, 14, 1000, L"Imagenes//SkyDomeNight.jpg");
		player->Charmander[0][0] = new EDXFramework::Model("Modelos//Charmander//CharmanderS0.obj", "Modelos//Charmander//Charmander.bmp", 1);
		player->Charmander[0][1] = new EDXFramework::Model("Modelos//Charmander//CharmanderS1.obj", "Modelos//Charmander//Charmander.bmp", 1);
		player->Charmander[0][2] = new EDXFramework::Model("Modelos//Charmander//CharmanderS0.obj", "Modelos//Charmander//Charmander.bmp", 1);
		player->Charmander[0][3] = new EDXFramework::Model("Modelos//Charmander//CharmanderS2.obj", "Modelos//Charmander//Charmander.bmp", 1);
		player->Charmander[1][0] = new EDXFramework::Model("Modelos//Charmander//Charmander0.obj", "Modelos//Charmander//Charmander.bmp", 1);
		player->Charmander[1][1] = new EDXFramework::Model("Modelos//Charmander//Charmander1.obj", "Modelos//Charmander//Charmander.bmp", 1);
		player->Charmander[1][2] = new EDXFramework::Model("Modelos//Charmander//Charmander2.obj", "Modelos//Charmander//Charmander.bmp", 1);
		player->Charmander[1][3] = new EDXFramework::Model("Modelos//Charmander//Charmander3.obj", "Modelos//Charmander//Charmander.bmp", 1);
		Trees[0] = new Object("Modelos//Palm//Palm2.obj", "Modelos//Palm//Palm.bmp", 1, 460, 460, terrain->Superficie(460,460) * 3 + 5);
		Trees[1] = new Object("Modelos//Palm//Palm2.obj", "Modelos//Palm//Palm.bmp", 1, 470, -470, terrain->Superficie(440, -470) * 3 + 5);
		Trees[2] = new Object("Modelos//Palm//Palm2.obj", "Modelos//Palm//Palm.bmp", 1, -470, -470, terrain->Superficie(-470, -470) * 3 + 5);
		Trees[3] = new Object("Modelos//Palm//Palm2.obj", "Modelos//Palm//Palm.bmp", 1, -470, 470, terrain->Superficie(-470, 470) * 3 + 5);
		Trees[4] = new Object("Modelos//Tree//Tree.obj", "Modelos//Tree//TreeTexture.bmp", 1, 370, 230, terrain->Superficie(370, 230) * 3 + 5);
		Trees[5] = new Object("Modelos//Tree//Tree.obj", "Modelos//Tree//TreeTexture.bmp", 1, -40, 150, terrain->Superficie(-40, 150) * 3 + 5);
		Trees[6] = new Object("Modelos//Tree//Tree.obj", "Modelos//Tree//TreeTexture.bmp", 1, 400, -10, terrain->Superficie(400, -10) * 3 + 5);
		Trees[7] = new Object("Modelos//Tree//Tree.obj", "Modelos//Tree//TreeTexture.bmp", 1, 10, -285, terrain->Superficie(10, -285) * 3 + 5);
		Trees[8] = new Object("Modelos//Tree//Tree.obj", "Modelos//Tree//TreeTexture.bmp", 1, -100, 440, terrain->Superficie(-100, 440) * 3 + 5);
		Trees[9] = new Object("Modelos//Tree//Tree.obj", "Modelos//Tree//TreeTexture.bmp", 1, -180, 250, terrain->Superficie(-18, 250) * 3 + 5);
		MiniMerry[0] = new AnimatedObject("Modelos//MiniMerry//MiniMerry.obj", "Modelos//MiniMerry//MerryTexturas.bmp", 1, 200, (terrain->Superficie(100, 30) * 3) + 17, -180);
		MiniMerry[1] = new AnimatedObject("Modelos//MiniMerry//MiniMerry2.obj", "Modelos//MiniMerry//MerryTexturas.bmp", 1, 200, (terrain->Superficie(100, 30) * 3) + 17, -180);
		MiniMerry2[0] = new AnimatedObject("Modelos//MiniMerry//MiniMerry.obj", "Modelos//MiniMerry//MerryTexturas.bmp", 1, 30, (terrain->Superficie(30, 190) * 3) + 17,  190);
		MiniMerry2[1] = new AnimatedObject("Modelos//MiniMerry//MiniMerry2.obj", "Modelos//MiniMerry//MerryTexturas.bmp", 1, 30, (terrain->Superficie(30, 190) * 3) + 17, 190);
		Porygon[0] = new AnimatedObject("Modelos//Porygon//Porygon.obj", "Modelos//Porygon//PorygonTexture.bmp", 1, -420, (terrain->Superficie(-420, 250) * 3) + 17, 250);
		Porygon[1] = new AnimatedObject("Modelos//Porygon//Porygon2.obj", "Modelos//Porygon//PorygonTexture.bmp", 1, -420, (terrain->Superficie(-420, 250) * 3) + 17, 250);
		Marril[0] = new AnimatedObject("Modelos//Marill//Marill.obj", "Modelos//Marill//MarillTexture.bmp", 1, -270, (terrain->Superficie(-270, -200) * 3) + 15, -200);
		Marril[1] = new AnimatedObject("Modelos//Marill//Marill2.obj", "Modelos//Marill//MarillTexture.bmp", 1, -270, (terrain->Superficie(-270, -200) * 3) + 15, -200);
		Marril[0]->setRotation(270);
		Meltan[0] = new AnimatedObject("Modelos//Meltan//Meltan.obj", "Modelos//Meltan//MeltanTexture.bmp", 1, -340, (terrain->Superficie(-340, -100) * 3) + 10, -100);
		Meltan[1] = new AnimatedObject("Modelos//Meltan//Meltan2.obj", "Modelos//Meltan//MeltanTexture.bmp", 1, -340, (terrain->Superficie(-340, -100) * 3) + 10, -100);
		TableNPB = new Object("Modelos//MesaPokeball//MesaYPokeball.obj", "Modelos//MesaPokeball//MesaTexture.bmp", 1, -430, 10, terrain->Superficie(-430, 10) * 3 + 10);
		Rock[0] = new Object("Modelos/Rock//Rock.obj", "Modelos//Rock//Roca.bmp", 1, -10, 90, (terrain->Superficie(-10, 90) * 3) + 10);
		Rock[1] = new Object("Modelos/Rock//Rock.obj", "Modelos//Rock//Roca.bmp", 1, -40, 140, (terrain->Superficie(-40, 140) * 3) + 10);
		Rock[2] = new Object("Modelos/Rock//Rock.obj", "Modelos//Rock//Roca.bmp", 1, 180, 160, (terrain->Superficie(170, 160) * 3) + 10);
		Rock[3] = new Object("Modelos/Rock//Rock.obj", "Modelos//Rock//Roca.bmp", 1, 190, 120, (terrain->Superficie(180, 120) * 3) + 10);

		Ramita[0]->SetRamitasRandom(Ramita, Trees, 10);
		for (short i = 0; i < 5; i++) {
			Ramita[i]->setY(terrain->Superficie(Ramita[i]->getX(), Ramita[i]->getZ()) * 3 + 10);
		}
		/*vector<thread> threads;*/

		wchar_t nametexture[100];
		for (short i = 0; i < 4; i++) {
			wcscpy_s(nametexture, L"");
			StringCchPrintfW(nametexture, 100, L"Imagenes//FireSequence//Fire%d.png", i + 1);
			flama[i] = new Billboard(hWnd, nametexture, 2, 2, 100, 100, 100);
			woodFire[i] = new Billboard(hWnd, nametexture, 10, 10, -440, 40, -50);
		}
		
		Billboards(billRain, hWnd);

		cameraInitialize();

	}

	void Billboards(Billboard *bills[], HWND hWnd){
		wchar_t nametexture[100];
		for (short i = 0; i < 14; i++) {
			wcscpy_s(nametexture, L"");
			StringCchPrintfW(nametexture, 100, L"Imagenes//RainSequence//Rain%d.png", i + 1);
			bills[i] = new Billboard(hWnd, nametexture, 100, 100, 100, 100, 100);
		}
	}

	void render(HDC hDC, Player* player){
		skyRotation < 360 ? skyRotation += 0.1f : skyRotation = 0;

		/*gunRotation < 360 ? gunRotation += 0.7f : gunRotation = 0;*/

		GameManagerC* GM = GameManagerC::getInstance();

		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glLoadIdentity();

		GLfloat AmbInt[] = { 0.1, 0.1, 0.1, 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
		//py = terrain->Superficie(px, pz) * 4 + 6;

		cameraUpdate();

		//Skydome
		glPushMatrix();
		glTranslatef(0, 8, 0);
		glRotatef(skyRotation, 0, 1, 0);
		skyDome[GM->DaynNight(AmbMat)]->Draw();
		glPopMatrix();

		//Lago
		glPushMatrix();
		glTranslatef(0, 17, 0);
		glScalef(5, 1, 5);
		lago->Draw();
		glPopMatrix();

		//Terreno
		glPushMatrix();
		glScalef(1, 4, 1);
		terrain->Draw();
		glPopMatrix();

		//Ramitas
		for (short j = 0; j < 5; j++) {
			glPushMatrix();
			glTranslatef(Ramita[j]->getX(), Ramita[j]->getY(), Ramita[j]->getZ());
			glScalef(15, 15, 15);
			Ramita[j]->Draw();
			glPopMatrix();
		}

		//Charmander
		MoverCharmander(&player,Getangle());

		//Tree
		for (short i = 0; i < 10; i++) {
			glPushMatrix();
			glTranslatef(Trees[i]->getX(), Trees[i]->getY(), Trees[i]->getZ());
			glScalef(.075, .075, .075);
			Trees[i]->Draw();
			glPopMatrix();
		}

		//Rocks
		for (short i = 0; i < 4; i++) {
			glPushMatrix();
			glTranslatef(Rock[i]->getX(), Rock[i]->getY(), Rock[i]->getZ());
			glScalef(5, 5, 5);
			Rock[i]->Draw();
			glPopMatrix();
		}

		//Table
		glPushMatrix();
		glTranslatef(TableNPB->getX(), TableNPB->getY()+2, TableNPB->getZ());
		glRotatef(180, 0, 1, 0);
		glScalef(10, 10, 10);
		TableNPB->Draw();
		glPopMatrix();

		//MiniMerry
		glPushMatrix();
		MiniMerry[0]->BoxAnimation();
		glTranslatef(MiniMerry[0]->getMovX(), MiniMerry[0]->getY(), MiniMerry[0]->getMovZ());
		glScalef(2.5, 2.5, 2.5);
		glRotatef(MiniMerry[0]->getRotation(), 0, 1, 0);
		MiniMerry[GM->getiObj()]->Draw();
		glPopMatrix();

		//MiniMerry2
		glPushMatrix();
		MiniMerry2[0]->BoxAnimation();
		glTranslatef(MiniMerry2[0]->getMovX(), MiniMerry2[0]->getY(), MiniMerry2[0]->getMovZ());
		glScalef(3, 3, 3);
		glRotatef(MiniMerry2[0]->getRotation(), 0, 1, 0);
		MiniMerry2[GM->getiObj()]->Draw();
		glPopMatrix();

		//Porygon
		glPushMatrix();
		if (!Porygon[0]->isReachable()) 
			glTranslatef(Porygon[0]->getMovX(), Porygon[0]->getY(), Porygon[0]->getMovZ());
		else {
			Porygon[0]->EscapeAnimation('x');
			Porygon[0]->setY(terrain->Superficie(Porygon[0]->getMovX(), Porygon[0]->getMovZ()) * 3 + 20);
			glTranslatef(Porygon[0]->getMovX(), Porygon[0]->getY(), Porygon[0]->getMovZ());
		}
			glScalef(3, 3, 3);
			glRotatef(Porygon[0]->getRotation(), 0, 1, 0);
			Porygon[GM->getiObj()]->Draw();
		glPopMatrix();

		//Marril
		glPushMatrix();
		if (!Marril[0]->isReachable())
			glTranslatef(Marril[0]->getMovX(), Marril[0]->getY(), Marril[0]->getMovZ());
		else {
			Marril[0]->EscapeAnimation('z');
			Marril[0]->setY(terrain->Superficie(Marril[0]->getMovX(), Marril[0]->getMovZ()) * 3 + 15);
			glTranslatef(Marril[0]->getMovX(), Marril[0]->getY(), Marril[0]->getMovZ());
		}
		glScalef(3, 3, 3);
		glRotatef(Marril[0]->getRotation(), 0, 1, 0);
		Marril[GM->getiObj()]->Draw();
		glPopMatrix();

		//Meltan
		glPushMatrix();
		glTranslatef(Meltan[0]->getMovX(), Meltan[0]->getY(), Meltan[0]->getMovZ());
		glScalef(11, 11, 11);
		glRotatef(Meltan[0]->getRotation(), 0, 1, 0);
		Meltan[GM->getiObj()]->Draw();
		glPopMatrix();

		//CentroPokemon
		glPushMatrix();
		glTranslatef(Estructuras[0][0]->getposx(), Estructuras[0][0]->gety(), Estructuras[0][0]->getposz());
		glRotatef(90, 0, 1, 0);
		glRotatef(2, 0, 0, 1);
		glScalef(.4, .32, .4);
		Estructuras[0][0]->Draw();
		glPopMatrix();

		//Hojas
		for (int j = 1; j < 10; j++) {
			glPushMatrix();
			glTranslatef(Estructuras[j][0]->getposx(), Estructuras[j][0]->gety(), Estructuras[j][0]->getposz());
			glScalef(6, 6, 6);
			Estructuras[j][GM->getiObj()]->Draw();
			glPopMatrix();
		}
				
		//Muelle
		glPushMatrix();
		glTranslatef(170.0f, 20, 135);
		glScalef(15, 3, 3);
		glRotatef(80, 0, 1, 0);
		Muelle->Draw();
		glPopMatrix();

		
		if (GM->getMessage() == WINNER) {
			glPushMatrix();
			woodFire[player->getiFlamita()]->Draw(px, py, pz);
			glPopMatrix();
		}

		//Flama
		glPushMatrix();
		flama[player->getiFlamita()]->Draw(dx, player->GetPosY(), dz, px, py, pz, -4.5, (player->getHealth()*.01));
		glPopMatrix();

		if (GM->isRaining() == true) {
			if (Estructuras[0][0]->isReachable() == false) {
				glPushMatrix();
				/*billBoard[player->getiFlamita()]->UpdatePlayerPosition(px, pz, py, dx, dz, dy);*/
					//billBoard[player->getiFlamita()]->Draw(player->GetPosX(), player->GetPosY()+5, player->GetPosZ(), px, py, pz);
				billRain[GM->getRainSprite()]->Draw(dx, dy, dz, px, py, pz, 10, 1.0);
				glPopMatrix();
			}
		}

		SwapBuffers(hDC);

	}

	~Scene(){
		//NO OLVIDES PONER AQUI TODOS TUS PUNTEROS
		delete Ramita[0];
		delete Ramita[1];
		delete Ramita[2];
		delete Ramita[3];
		delete Ramita[4];
		delete Trees[0];
		delete Trees[1];
		delete Trees[2];
		delete Trees[3];
		delete Trees[4];
		delete Trees[5];
		delete Trees[6];
		delete Trees[7];
		delete Trees[8];
		delete Trees[9];
		delete skyDome[0];
		delete skyDome[1];
		delete terrain;
		delete Estructuras[0][0];
		delete Estructuras[1][0];
		delete Estructuras[2][0];
		delete Estructuras[3][0];
		delete Estructuras[4][0];
		delete Estructuras[5][0];
		delete Estructuras[6][0];
		delete Estructuras[7][0];
		delete Estructuras[8][0];
		delete Estructuras[9][0];
		delete Estructuras[0][1];
		delete Estructuras[1][1];
		delete Estructuras[2][1];
		delete Estructuras[3][1];
		delete Estructuras[4][1];
		delete Estructuras[5][1];
		delete Estructuras[6][1];
		delete Estructuras[7][1];
		delete Estructuras[8][1];
		delete Estructuras[9][1];
		delete billRain[0];
		delete billRain[1];
		delete billRain[2];
		delete billRain[3];
		delete billRain[4];
		delete billRain[5];
		delete billRain[6];
		delete billRain[7];
		delete billRain[8];
		delete billRain[9];
		delete billRain[10];
		delete billRain[11];
		delete billRain[12];
		delete billRain[13];
		delete flama[0];
		delete flama[1];
		delete flama[2];
		delete flama[3];
		delete woodFire[0];
		delete woodFire[1];
		delete woodFire[2];
		delete woodFire[3];
		delete MiniMerry[0];
		delete MiniMerry[1];
		delete MiniMerry2[0];
		delete MiniMerry2[1];
		delete Porygon[0];
		delete Porygon[1];
		delete Marril[0];
		delete Marril[1];
		delete lago;
		delete Meltan[0];
		delete Meltan[1];
		delete TableNPB;
		delete Muelle;
		delete Rock[0];
		delete Rock[1];
		delete Rock[2];
		delete Rock[3];
		//delete Nosepass;
		///*delete Snourunt;*/
		
	}

	void reStartSceneValues() {
		cameraInitialize();
		Ramita[0]->SetRamitasRandom(Ramita, Trees, 10);
		for (short i = 0; i < 5; i++) {
			Ramita[i]->setY(terrain->Superficie(Ramita[i]->getX(), Ramita[i]->getZ()) * 3 + 12);
		}
		skyRotation = 0;
	}

	void MoverCharmander(Player** player, GLdouble angle) {
		glPushMatrix();
		//scene->Getdx(), (scene->terrain->Superficie(scene->Getdx(), scene->Getdz())), scene->Getdz(), scene->Getangle()
		glTranslatef((*player)->GetPosX(), (*player)->GetPosY()-5, (*player)->GetPosZ());
		glRotatef(-(angle), 0, 1, 0);
		glScalef(2, 2, 2);
			(*player)->Charmander[(*player)->GetStateChar()][(*player)->GetiChar()]->Draw();
		glPopMatrix();
	}
};

//void CargarTerreno(Terrain** Ter, HWND hWnd) {
//	*Ter = new Terrain(hWnd, L"C://Users//edson//Desktop//MapaPrueba.jpg", L"Imagenes//test1.jpg", L"Imagenes//test1.jpg", 512, 512);
//}
	

#endif
