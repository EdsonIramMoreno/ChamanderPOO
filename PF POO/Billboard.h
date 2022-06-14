#ifndef _billb
#define _billb
#include "Imagenes.h"
#include "VectorRR.h"
#include "Player.h"

class Billboard: public Imagenes, public VectorRR {
	float ancho, alto;
	unsigned int billbTextura;
	VectorRR Up, derecha;
	GLdouble x, y, z;
	VectorRR BillCam;

	void UpdatePlayerPosition(float xp, float zp, float yp, float cpx, float cpz, float cpy, int menosy) {
		float Posx = 1, Posz = 1, Posy = 1;
		Posx = cpx + xp;
		Posx = Posx * .5;
		Posz = cpz + zp;
		Posz = Posz * .5;
		this->x = Posx;
		if (menosy != 10) {
			Posy = yp + cpy;
			Posy = Posy * .5 - menosy;
		}
		else
			Posy = yp- menosy;
		//this->y = yp - menosy;
		this->y = Posy;
		this->z = Posz;
	}

	void anchoalto(float tam) {
		//float tamano = tam * .10;
		derecha.X = derecha.X * (ancho * tam) / 2.0;
		derecha.Z = derecha.Z * (ancho * tam) / 2.0;
		alto = alto * tam;
	}
public:

	void Draw(GLdouble PX, GLdouble PY, GLdouble PZ)
	{

		//habilitamos el culling para reducir tiempo de procesamiento de las texturas
		//las texturas se analizan pixel a pixel para determinar que se imprimen o no
		//por lo que aunque no la veamos nos costo, por eso la eliminamos.
		glEnable(GL_CULL_FACE);
		//hay dos tipos de cull el frontal y el trasero (back)
		glCullFace(GL_FRONT);
		//habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
		//con glColorxf
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		glEnable(GL_TEXTURE_2D);
		//usamos modulate para que la textura sea afectada por el valor de la normal en cuanto
		//a luz
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, billbTextura);
		//calculamos el vector de la camara al billboard
		BillCam = VectorRR(PX - this->x, PY - this->y, PZ - this->z);
		//obtenemos 
		derecha = Normaliza(Cruz(Up, BillCam));
		derecha.X *= ancho / 2.0;
		derecha.Z *= ancho / 2.0;

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(this->x - derecha.X, this->y + alto, this->z - derecha.Z);

		glTexCoord2f(1, 0);
		glVertex3f(this->x + derecha.X, this->y + alto, this->z + derecha.Z);

		glTexCoord2f(1, 1);
		glVertex3f(this->x + derecha.X, this->y, this->z + derecha.Z);

		glTexCoord2f(0, 1);
		glVertex3f(this->x - derecha.X, this->y, this->z - derecha.Z);
		glEnd();
		glDisable(GL_CULL_FACE);
		glDisable(GL_ALPHA);
		glDisable(GL_BLEND);
	}

	Billboard(HWND hWnd, WCHAR textura[], float ancho, float alto, float x, float y, float z){
		this->ancho = ancho;
		this->alto = alto;	
		this->x = x;
		this->y = y;
		this->z = z;
		Up = VectorRR(0,1,0);
		//este vector es el que nos dara el ancho del billboard
		//cada vez que lo giremos segun la camara
		
		Carga(textura);
		glGenTextures(1, &billbTextura);
		glBindTexture(GL_TEXTURE_2D, billbTextura);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Ancho(), Alto(), GL_RGBA, GL_UNSIGNED_BYTE, Dir_Imagen());
		Descarga();				
	}

	~Billboard(){		
		glDeleteTextures(1, &billbTextura);
	}

	//void Draw(GLdouble PX, GLdouble PY, GLdouble PZ){
	//	this->x = PX;
	//	this->y = PY;
	//	this->z = PZ;
	//	//habilitamos el culling para reducir tiempo de procesamiento de las texturas
	//	//las texturas se analizan pixel a pixel para determinar que se imprimen o no
	//	//por lo que aunque no la veamos nos costo, por eso la eliminamos.
	//	glEnable(GL_CULL_FACE);
	//	//hay dos tipos de cull el frontal y el trasero (back)
	//	glCullFace(GL_FRONT);
	//	//habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
	//	//con glColorxf
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glEnable(GL_ALPHA_TEST);
	//	glAlphaFunc(GL_GREATER, 0);
	//	glEnable(GL_TEXTURE_2D);
	//	//usamos modulate para que la textura sea afectada por el valor de la normal en cuanto
	//	//a luz
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//	glBindTexture(GL_TEXTURE_2D, billbTextura);
	//	//calculamos el vector de la camara al billboard
	//	BillCam = VectorRR(this->x,this->y,this->z);
	//	//obtenemos 
	//	derecha = Normaliza(Cruz(Up, BillCam));
	//	derecha.X *= ancho / 2.0;
	//	derecha.Z *= ancho / 2.0;
	//	glBegin(GL_QUADS);
	//	glTexCoord2f(0, 0);
	//	glVertex3f(this->x - derecha.X, this->y + alto, this->z - derecha.Z);
	//	glTexCoord2f(1, 0);
	//	glVertex3f(this->x + derecha.X, this->y + alto, this->z + derecha.Z);
	//	glTexCoord2f(1, 1);
	//	glVertex3f(this->x + derecha.X, this->y, this->z + derecha.Z);
	//	glTexCoord2f(0, 1);
	//	glVertex3f(this->x - derecha.X, this->y, this->z - derecha.Z);
	//	glEnd();
	//	glDisable(GL_CULL_FACE);
	//	glDisable(GL_ALPHA);
	//	glDisable(GL_BLEND);
	//}

	void Draw(float px, float py, float pz, GLdouble CPX, GLdouble CPY, GLdouble CPZ, int menosy, float tam) {
		float aux = alto;
		UpdatePlayerPosition(px, pz, py, CPX, CPZ, CPY, menosy);
		/*this->x = x;
		this->y = y;
		this->z = z;*/

		//habilitamos el culling para reducir tiempo de procesamiento de las texturas
		//las texturas se analizan pixel a pixel para determinar que se imprimen o no
		//por lo que aunque no la veamos nos costo, por eso la eliminamos.
		glEnable(GL_CULL_FACE);
		//hay dos tipos de cull el frontal y el trasero (back)
		glCullFace(GL_FRONT);
		//habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
		//con glColorxf
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		glEnable(GL_TEXTURE_2D);
		//usamos modulate para que la textura sea afectada por el valor de la normal en cuanto
		//a luz
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, billbTextura);
		//calculamos el vector de la camara al billboard
		BillCam = VectorRR(CPX - this->x, CPY - this->y, CPZ - this->z);
		//obtenemos 
		derecha = Normaliza(Cruz(Up, BillCam));
		anchoalto(tam);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);

		glVertex3f(this->x - derecha.X, this->y + alto, this->z - derecha.Z);

		glTexCoord2f(1, 0);
		glVertex3f(this->x + derecha.X, this->y + alto, this->z + derecha.Z);

		glTexCoord2f(1, 1);
		glVertex3f(this->x + derecha.X, this->y, this->z + derecha.Z);

		glTexCoord2f(0, 1);
		glVertex3f(this->x - derecha.X, this->y, this->z - derecha.Z);
		glEnd();
		alto = aux;
		glDisable(GL_CULL_FACE);
		glDisable(GL_ALPHA);
		glDisable(GL_BLEND);
	}

	//void draw(float px, float py, float pz, GLdouble CPX, GLdouble CPY, GLdouble CPZ, int tam, float posy) {
	//	UpdatePlayerPositionF(px, pz, CPX, CPZ, posy);
	//	/*this->x = x;
	//	this->y = y;
	//	this->z = z;*/

	//	//habilitamos el culling para reducir tiempo de procesamiento de las texturas
	//	//las texturas se analizan pixel a pixel para determinar que se imprimen o no
	//	//por lo que aunque no la veamos nos costo, por eso la eliminamos.
	//	glEnable(GL_CULL_FACE);
	//	//hay dos tipos de cull el frontal y el trasero (back)
	//	glCullFace(GL_FRONT);
	//	//habilitamos la textura, podriamos mezclar colores y cambiar la tonalidad de la textura
	//	//con glColorxf
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glEnable(GL_ALPHA_TEST);
	//	glAlphaFunc(GL_GREATER, 0);
	//	glEnable(GL_TEXTURE_2D);
	//	//usamos modulate para que la textura sea afectada por el valor de la normal en cuanto
	//	//a luz
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//	glBindTexture(GL_TEXTURE_2D, billbTextura);
	//	//calculamos el vector de la camara al billboard
	//	BillCam = VectorRR(CPX - this->x, CPY - this->y, CPZ - this->z);
	//	//obtenemos 
	//	derecha = Normaliza(Cruz(Up, BillCam));
	//	float tamano = derecha.X;
	//	tamano *= (tam * .10);
	//	derecha.X = tamano / 4.0; // * (tam * .10)
	//	tamano = derecha.Z;
	//	tamano *= (tam * .10);
	//	derecha.Z *= tamano / 4.0;
	//	//derecha.X *= ancho / 2.0; // * (tam * .10)
	//	//derecha.Z *= ancho / 2.0;

	//	glBegin(GL_QUADS);
	//	glTexCoord2f(0, 0);
	//	glVertex3f(this->x - derecha.X, this->y + alto, this->z - derecha.Z);

	//	glTexCoord2f(1, 0);
	//	glVertex3f(this->x + derecha.X, this->y + alto, this->z + derecha.Z);

	//	glTexCoord2f(1, 1);
	//	glVertex3f(this->x + derecha.X, this->y, this->z + derecha.Z);

	//	glTexCoord2f(0, 1);
	//	glVertex3f(this->x - derecha.X, this->y, this->z - derecha.Z);
	//	glEnd();
	//	glDisable(GL_CULL_FACE);
	//	glDisable(GL_ALPHA);
	//	glDisable(GL_BLEND);
	//}

	//void UpdatePlayerPositionF(float xp, float zp, float cpx, float cpz, float posY) {
	//	float Posx = 1, Posz = 1;
	//	Posx = cpx + xp;
	//	if (Posx != 0) {
	//		Posx = Posx * .5;
	//	}
	//	Posz = cpz + zp;
	//	if (Posz != 0) {
	//		Posz = Posz * .5;
	//	}
	//	this->x = Posx;
	//	this->y = posY + 2;
	//	this->z = Posz;
	//}
};

#endif 