#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>
#include"gunit/BSPMap.h"

using namespace std;
using namespace siege::math;
using namespace siege::gunit;

GLuint width = 800;
GLuint height = 800;
float trans = -3000.0;
float rotfact;
Vector3 cam(0,0,0);

BSPMap map;
 

// Kill program
void endProgram(int code) {
	SDL_Quit();
	exit(code);
	}
 
// Handle SDL keypresses
void handleKeys(SDL_keysym* keysym, bool state) {
    if(state)switch(keysym->sym) {
        case SDLK_ESCAPE:    endProgram(0); break;
        case SDLK_DOWN:    trans -= 100; break;
        case SDLK_UP:    trans += 100; break;
        case SDLK_RIGHT:    rotfact += 1; break;
        case SDLK_LEFT:    rotfact -= 1; break;
        case SDLK_w:    cam[1] += 50; break;
        case SDLK_s:    cam[1] -= 50; break;
        case SDLK_d:    cam[0] -= 50; break;
        case SDLK_a:    cam[0] += 50; break;
        case SDLK_q:    cam[2] += 50; break;
        case SDLK_e:    cam[2] -= 50; break;
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


	float f1[3];
	float f2[3];
	float f3[3];

   	while(true) {
        processEvents();
 
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
		glTranslatef(0.0, 0.0, trans);
		glRotatef(rotfact, 0,1,0);
		Vector3 v1 = cam;
		v1[0] -= 100;
		Vector3 v2 = cam;
		v2[0] += 100;
		Vector3 v3 = cam;
		v3[1] += 100;


		map.draw();

		glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			v1.get(f1);
			v2.get(f2);
			v3.get(f3);
			glVertex3fv(f1);
			glVertex3fv(f2);
			glVertex3fv(f3);

		glEnd();

        SDL_GL_SwapBuffers();
	}
}
void setupOpengl() {
    glViewport(0, 0, width, height);
    //glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    gluPerspective(45, (float)width/height, .1, 100000);
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

	map.load((char*)"data/map/maps/q3shw18.bsp");

    mainLoop();
    return 0;
}
