#include <Windows.h>
#include "glew.h"
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Scene.h"
#include <time.h>
#include "GamePadRR.h"
#include "resource.h"
#include <thread>
#include <strsafe.h>
#include "Player.h"
#include "Terrain.h"
#include "GameManagerC.h"
#include "Object.h"
#pragma comment (lib, "glew32.lib") 
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 

#define Timer1 150

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DefPixelFormat(HDC hDC);
void gamepad(XINPUT_STATE, HWND);

Player* player = new Player();
HWND hInfo = 0;
HWND hText = 0;
bool ableToCheck = false;
HDC hContextoVentana;
Scene *scene;
GamePadRR *gamPad;
XINPUT_STATE Control;
bool renderiza = false;
unsigned int dayTimer = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	HWND hwndVentana;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX); //Tamaño en bytes de la estructura.
	wc.style = CS_HREDRAW | CS_VREDRAW; //Entero de 16 bits que codifica el estilo de la clase de ventana.
	wc.lpfnWndProc = WindowProc;//Apunta al procedimiento de ventana.
	wc.hInstance = hInstance;//Identifica la instancia de la ventana a la que esta clase pertenece.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Identificador del curso de la clase. Debe ser un manipulador de un recurso de tipo icono. Si es Null, la aplicación mostrará un icono cuando el usuario minice la ventana de la aplicación.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //Identificador del pincel para la clase.
	wc.lpszClassName = "DavidWindow"; //Especifica el nombre de la clase ventana.
	RegisterClassEx(&wc);//Registra una clase de ventana para su uso subsecuente en llamadas a las funciones CreateWindow o CreateWindowEx
	RECT wr = { 0, 0, 1080, 720 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);//Calcula el tamaño necesario del rectángulo de la ventana.
	//Se crea la ventana definida previamente.
	hwndVentana = CreateWindowEx(NULL,//estilo extendido de ventana
		"DavidWindow",//puntero al nombre de la clase registrada *visto arriba*
		"Charmander",//puntero al nombre de la ventana
		WS_OVERLAPPEDWINDOW,//estilo de ventana
		0,//posición horizontal de la ventana
		0,//posición vertical de la ventana
		wr.right - wr.left,//ancho de la ventana
		wr.bottom - wr.top,//alto de la ventana
		NULL,//manejador de la ventana padre o propietaria
		NULL,//manejador del menu o identificador de ventana hija
		hInstance,//manejador de la instancia de la aplicación
		NULL);//puntero a los datos de creación de la ventana

	ShowWindow(hwndVentana, nCmdShow);//Muestra la ventana creada
	GameManagerC* GM = GameManagerC::getInstance();
	
	ShowWindow(hInfo, SW_SHOW);
	
	glewInit();//Inicializa glew

	//Instancia de la escena
	scene = new Scene(hwndVentana, player);
	
	gamPad = new GamePadRR(1);
	ableToCheck = true;

	//Crear un timer con el valor especificado de time-out
	SetTimer(hwndVentana,//Manejador de ventana que recibirá los mensajes del timer
		Timer1,//identificador del timer
		60,//valor de time-out
		NULL);//dirección del procedimiento de timer

	MSG msg = { 0 };
	while (TRUE){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else{
			if (renderiza){			
				scene->render(hContextoVentana,player);
				renderiza = false;
				if (gamPad->IsConnected()){
					//PISTA: Algo puedes lograr aqui con ayuda del autocompletador
					Control = gamPad->GetState();
					gamepad(Control, hwndVentana);
				}
			}
		}
	}
	delete player;
	return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	static HGLRC hContextoGL;
	static HDC hContextoAux;
	int ancho, alto;
	char epx[6] = "";
	char epz[6] = "";
	char epy[6] = "";
	char edx[6] = "";
	char edz[6] = "";
	char edy[6] = "";
	char ec[80] = "";
	GameManagerC* GM = GameManagerC::getInstance();
	switch (message){
	case WM_CREATE:{
		hContextoAux = GetDC(hWnd);
		hContextoVentana = hContextoAux;
		DefPixelFormat(hContextoVentana);
		hContextoGL = wglCreateContext(hContextoVentana);
		wglMakeCurrent(hContextoVentana, hContextoGL);
		srand(time(NULL));
		}
			break;
	case WM_KEYUP: {
		if (wParam == VK_LEFT || wParam == VK_RIGHT || wParam == 0x44 || wParam == 0x41 || wParam == 0x57 || wParam == 0x53) {
			player->SetStateChar(0);
		}
	}
		break;
	case WM_KEYDOWN:
		switch (wParam){
		case ' ':{
			char Info[100] = { '\0' };
			StringCchPrintf(Info, 100, "Vida: %d    Ramitas: %d\nPosicion:\n X: %.2f  Y: %.2f  Z: %.2f",
				player->getHealth(), player->getRamitas(), scene->Getdx(), scene->Getdy(), scene->Getdz());
			MessageBox(hWnd, Info, "Inforamción jugador", MB_OK);
		}
			break;
		case VK_LEFT: {
			player->SetStateChar(1);
			if (GM->getMov())
				scene->turnLeft();
			else
				scene->turnRight();
			renderiza = true;
		}
			break;
		case VK_RIGHT: {
			player->SetStateChar(1);
			if (GM->getMov())
				scene->turnRight();
			else
				scene->turnLeft();
			renderiza = true;
		}
			break;
		case 0x44: { //D
			player->SetStateChar(1);
			if (GM->getMov())
				scene->move('r');
			else
				scene->move('l');
			renderiza = true;
		}
			break;
		case 0x41: { //A
			player->SetStateChar(1);
			if (GM->getMov())
				scene->move('l');
			else
				scene->move('r');
			renderiza = true;
		}
			break;
		case 0x57: { //W
			player->SetStateChar(1);
			if (GM->getMov())
				scene->move('f');
			else
				scene->move('b');
			renderiza = true;
		}
			break;
		case 0x53: { //S
			player->SetStateChar(1);
			if (GM->getMov())
				scene->move('b');
			else
				scene->move('f');
			renderiza = true;
		}
			break;
		case 'Q': {
			if (player->isableToPickRamita()) {
				player->incTRamas();
				for (short i = 0; i < 5; i++) {
					if (scene->Ramita[i]->isReachable()) {
						scene->Ramita[i]->setX(-445);
						scene->Ramita[i]->setZ(-63 + (player->getRamitas() * 3));
						scene->Ramita[i]->setY(scene->terrain->Superficie(scene->Ramita[i]->getX(), scene->Ramita[i]->getZ() * 3) + 30);
						scene->Ramita[i]->setReachable(false);
					}
				}
				if (player->getRamitas() == 5) {
					//GM->MessageShowed = true;
					GM->setMessage(TASK_COMPLETED);
				}
			}
		}
			break;
		case 'I': {
			string info = "\tControles \nMovimiento: A,D,W,S \n  Vista: <-,-> \n  Recolectar: Q \n  Reiniciar: R \n  Jugador: space";
			MessageBox(hWnd, info.c_str(), "INFO", MB_OK);
		}
				break;
		case 'R':{
			GM->setMessage(RESTART);
			}
			break;
		case 'E': {
			if (player->getRamitas() == 5) {
				if ((player->GetPosX() >= -435 && player->GetPosX() <= -425) &&
					player->GetPosZ() >= -60 && player->GetPosZ() <= -40) {
					GM->setMessage(WINNER);
				}
			}
		}
			break;
		}
		break;
	case WM_TIMER:{
		if (GM->CrossRiver(player)) {
			(scene)->dy = 35;
			(player)->setCharmanderPos((scene)->Getdx(), (scene)->Getdy(), (scene)->Getdz());
			(scene)->py = (scene)->dy + 5;
		}
		else {
			(scene)->dy = (scene)->terrain->Superficie((scene)->dx, (scene)->dz) * 3 + 20;
			(player)->setCharmanderPos((scene)->Getdx(), (scene)->Getdy() - 3, (scene)->Getdz());
			(scene)->py = ((scene)->terrain->Superficie((scene)->px, (scene)->pz) * 4) + 7.5;
		}

		GM->ManageGame(&player, hWnd, scene->Ramita, scene->Estructuras, scene->Porygon[0], scene->Marril[0], scene->Getdx(), scene->Getdz());
		bool a = GM->isInsideStructure(player, scene->Estructuras);

		if (GM->getMessage() == TIME_D_WIN) {
			GM->setMessage(Nothing);
			int a = MessageBoxA(hWnd, "Has ganado, \n¿Quieres volver a jugar?", "Felicidades", MB_YESNO);
			if (a == IDNO || a==IDCLOSE) {
				PostQuitMessage(0);
				DestroyWindow(hWnd);
			}
			else if(a==IDYES){
				scene->reStartSceneValues();
				player->reStartPlayerValues();
				GM->reStartGameValues();
			}
		}

		if (GM->getMessage() == LOSER) {
			GM->setMessage(DEAD_CHECKED);
			int a = MessageBoxA(hWnd, "Has perdido, \n¿Quieres volver a jugar?", "GAME OVER", MB_YESNO);
			if (a == IDNO || a == IDCLOSE) {
				PostQuitMessage(0);
				DestroyWindow(hWnd);
			}
			else if (a == IDYES) {
				scene->reStartSceneValues();
				player->reStartPlayerValues();
				GM->reStartGameValues();
			}
		}

		if (GM->getMessage() == TASK_COMPLETED) {
			GM->setMessage(Nothing);
			MessageBoxA(hWnd, "Haz recolectado las 5 ramitas,\n regresa a la casa.", "Misión Cumplida", MB_OK);
		}

		if (GM->getMessage() == RESTART) {
			GM->setMessage(Nothing);
			int a = MessageBoxA(hWnd, "¿Seguro quiere reiniciar el juego?", "Reiniciar", MB_YESNO);
			if (a == IDYES) {
				scene->reStartSceneValues();
				player->reStartPlayerValues();
				GM->reStartGameValues();
			}
		}

		renderiza = true;
	}
		break;
	case WM_DESTROY:{
		KillTimer(hWnd, Timer1);
		delete scene;
		wglMakeCurrent(hContextoVentana, NULL);
		wglDeleteContext(hContextoGL);
		/*DeleteSprites(ImagenSprites);
		SelectObject(mhDC, mhOldObject);
		DeleteObject(mhSurface);
		DeleteDC(mhDC);*/
		PostQuitMessage(0);
		break;
	} 
		break;
	case WM_SIZE:{
		alto = HIWORD(lParam);
		ancho = LOWORD(lParam);
		if (alto == 0)
			alto = 1;
		glViewport(0, 0, ancho, alto);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)ancho / (GLfloat)alto, 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DefPixelFormat(HDC hDC){
	int bestmatch;
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), //tamaño de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tamaño del color en 32 bits
		0, 0, 0, 0, 0, 0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0, 0, 0, 0, //no hay bits de acumulacion
		16, //tamaño del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0, 0, 0 //mascaras de capas ignoradas
	};
	bestmatch = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, bestmatch, &pfd);
}

void gamepad(XINPUT_STATE Gamepad, HWND hWnd) {
	GameManagerC* GM = GameManagerC::getInstance();
	if ((Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) || (Gamepad.Gamepad.sThumbLY >= 22000 && Gamepad.Gamepad.sThumbLY <= 33000)) {
		player->SetStateChar(1);
		if (GM->getMov())
			scene->move('f');
		else
			scene->move('b');
	}
	else if ((Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) || (Gamepad.Gamepad.sThumbLY >= -33000 && Gamepad.Gamepad.sThumbLY <= -22000)) {
		player->SetStateChar(1);
		if (GM->getMov())
			scene->move('b');
		else
			scene->move('f');
	}
	else if ((Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) || (Gamepad.Gamepad.sThumbLX >= -33000 && Gamepad.Gamepad.sThumbLX <= -22000)) {
		player->SetStateChar(1);
		if (GM->getMov())
			scene->move('l');
		else
			scene->move('r');
	}
	else if ((Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) || (Gamepad.Gamepad.sThumbLX >= 22000 && Gamepad.Gamepad.sThumbLX <= 33000)) {
		player->SetStateChar(1);
		if (GM->getMov())
			scene->move('r');
		else
			scene->move('l');
	}
	else if (Gamepad.Gamepad.sThumbRX >= -33000 && Gamepad.Gamepad.sThumbRX <= -26000) {
		player->SetStateChar(1);
		if (GM->getMov())
			scene->turnLeft();
		else
			scene->turnRight();
	}
	else if (Gamepad.Gamepad.sThumbRX >= 26000 && Gamepad.Gamepad.sThumbRX <= 33000) {
		player->SetStateChar(1);
		if (GM->getMov())
			scene->turnRight();
		else
			scene->turnLeft();
	}
	else if (Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_START) {
		char Info[100] = { '\0' };
		StringCchPrintf(Info, 100, "Vida: %d    Ramitas: %d\nPosicion:\n X: %.2f  Y: %.2f  Z: %.2f", 
			player->getHealth(), player->getRamitas(), scene->Getdx(), scene->Getdy(), scene->Getdz());
			MessageBox(hWnd, Info, "Inforamción jugador", MB_OK);
	}
	else if (Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
		GM->setMessage(RESTART);
	}
	else if (Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		string info = "\tControles \nMovimiento: joystick I \n  Vista: joystick D \n  Recolectar: A \n  Reiniciar: Back \n  Jugador: Start";
		MessageBox(hWnd, info.c_str(), "INFO", MB_OK);
	}
	else if (Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		if (player->isableToPickRamita()) {
			player->incTRamas();
			for (short i = 0; i < 5; i++) {
				if (scene->Ramita[i]->isReachable()) {
					scene->Ramita[i]->setX(-445);
					scene->Ramita[i]->setZ(-60 + (player->getRamitas() * 3));
					scene->Ramita[i]->setY(scene->terrain->Superficie(scene->Ramita[i]->getX(), scene->Ramita[i]->getZ() * 3) + 30);
					scene->Ramita[i]->setReachable(false);
				}
			}
			if (player->getRamitas() == 5) {
				GM->setMessage(TASK_COMPLETED);
			}
		}
	}
	else if (Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		if (player->getRamitas() == 5) {
			if ((player->GetPosX() >= -435 && player->GetPosX() <= -425) &&
				player->GetPosZ() >= -60 && player->GetPosZ() <= -40) {
				GM->setMessage(WINNER);
			}
		}
	}
	else
		player->SetStateChar(0);
}

