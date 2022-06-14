#ifndef __Fog
#define __Fog

#include <gl\GLU.h>
#include <gl\GL.h>

class Fog
{
public:
	GLfloat Color[4];
	GLfloat density;
	void draw() {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_FOG); 
		glFogi(GL_FOG_MODE, GL_EXP2); 
		glFogfv(GL_FOG_COLOR, Color); 
		glFogf(GL_FOG_DENSITY, density);
		glHint(GL_FOG_HINT, GL_NICEST);

	}
};

#endif