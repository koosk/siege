#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>
#include"math/Matrix4.h"

using namespace std;
using namespace siege::math;

GLuint width = 800;
GLuint height = 800;
float trans = -30.0;
float rotfact;

 

// Kill program
void endProgram(int code) {
	SDL_Quit();
	exit(code);
	}
 
// Handle SDL keypresses
void handleKeys(SDL_keysym* keysym, bool state) {
    if(state)switch(keysym->sym) {
        case SDLK_ESCAPE:    endProgram(0); break;
        case SDLK_DOWN:    trans -= 50; break;
        case SDLK_UP:    trans += 50; break;
        case SDLK_RIGHT:    rotfact += .5; break;
        case SDLK_LEFT:    rotfact -= .5; break;
        default: break;
    }
}
 
// Process SDL events
void processEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:    handleKeys(&event.key.keysym, true ); break;
            case SDL_KEYUP  : handleKeys(&event.key.keysym, false);    break;
            case SDL_QUIT   : endProgram(0); break;
        }
    }
}
 
void mainLoop() {
	Vector3 v1(0, 3, 0);
	Vector3 v2(-3, 0, 0);
	Vector3 v3(3, 0, 0);

	Vector3 v4(-1, 0, 0);
	Vector3 v5(0, 1, 0);
	Vector3 v6(1, 0, 0);

	Vector3 vr(0., 0.001, 0.001);
	Vector3 vr2(0.0, 0.01, 0);
	Vector3 vt(3, 0., 0);
	Vector3 vt2(0, 4, 0);
	float f1[3];
	float f2[3];
	float f3[3];
	Matrix4 m, m2;
	cout << m << endl;
	m = m.translate(vt);
	cout << m << endl;
	cout<<"Elott1:" << v1 << endl;
	cout<<"Elott2:" << v2 << endl;
	cout<<"Elott3:" << v3 << endl;
	v1 = v1*m;
	v2 = v2*m;
	v3 = v3*m;
	cout<<"Utan1:" << v1 << endl;
	cout<<"Utan2:" << v2 << endl;
	cout<<"Utan3:" << v3 << endl;
	m = Matrix4();
	m = m.rotate(vr);
	m2 = m2.rotate(vr2);

	Matrix4 m3;


   	while(true) {
        processEvents();
 
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
		glTranslatef(0.0, 0.0, trans);
		glRotatef(rotfact, 0,1,0);

		Vector3 vv1 = v4, vv2 = v5, vv3 = v6;
		Matrix4 m4;
		m4 = m4.translate(v1);
		m3 = m3*m2;


		vv1 = vv1*m4;
		vv2 = vv2*m4;
		vv3 = vv2*m4;

		vv1 = vv1*m3;
		vv2 = vv2*m3;
		vv3 = vv2*m3;

		float tmp[4] = {.5, .5, .5, 1};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, tmp);

		glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			v1.get(f1);
			v2.get(f2);
			v3.get(f3);
			glVertex3fv(f1);
			glVertex3fv(f2);
			glVertex3fv(f3);

			glColor3f(0, 0, 1);
			vv1.get(f1);
			vv2.get(f2);
			vv3.get(f3);
			glVertex3fv(f1);
			glVertex3fv(f2);
			glVertex3fv(f3);
		glEnd();

        SDL_GL_SwapBuffers();

		v1 = v1*m;
		v2 = v2*m;
		v3 = v3*m;

    }
}
void setupOpengl() {
    glViewport(0, 0, width, height);
    //glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    gluPerspective(45, (float)width/height, .1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	

	GLfloat ambient[] = {.5, .5, .5, 1};
	GLfloat diffuse[] = {1, 1, 1, 1};
	GLfloat pos[] = {0, 50, -50, 1};
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, pos);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);	
	glEnable(GL_LIGHTING);

    glEnable( GL_TEXTURE_2D );
	SDL_EnableKeyRepeat( 100, SDL_DEFAULT_REPEAT_INTERVAL );

}
 
// Init everything
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(width, height, 24, SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
    setupOpengl();

    mainLoop();
    return 0;
}
