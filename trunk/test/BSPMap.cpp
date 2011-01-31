#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>
#include"gunit/BSPMap.h"
#include"scene/Camera.h"

using namespace std;
using namespace siege::math;
using namespace siege::gunit;
using namespace siege::scene;

GLuint width = 800;
GLuint height = 800;
float rotfact1;
float rotfact2;
float rotfact3;
Vector3 cam(0,0,0);
Vector3 pos(0,0,0);
Vector3 rot(0,0,0);
float tim = 0;

Camera c;

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
        case SDLK_DOWN:    rot[0] += 1*tim; break;
        case SDLK_UP:    rot[0] -= 1*tim; break;
        case SDLK_RIGHT:    rot[1] += 1*tim; break;
        case SDLK_LEFT:    rot[1] -= 1*tim; break;
        case SDLK_KP8:    c.move(Camera::MOVE_FORWARD); break;
        case SDLK_KP2:    c.move(Camera::MOVE_BACKWARD); break;
        case SDLK_KP4:    c.rotate(Camera::ROTATE_UP); break;
        case SDLK_KP6:    c.rotate(Camera::ROTATE_DOWN); break;
        case SDLK_KP7:    c.rotate(Camera::ROTATE_LEFT);  break;
        case SDLK_KP9:    c.rotate(Camera::ROTATE_RIGHT); break;
        /*case SDLK_KP8:    pos[1] -= 50*tim; break;
        case SDLK_KP2:    pos[1] += 50*tim; break;
        case SDLK_KP4:    pos[0] -= 50*tim; break;
        case SDLK_KP6:    pos[0] += 50*tim; break;
        case SDLK_KP7:    pos[2] += 50*tim; break;
        case SDLK_KP9:    pos[2] -= 50*tim; break;
        */case SDLK_w:    cam[1] += 50*tim; break;
        case SDLK_s:    cam[1] -= 50*tim; break;
        case SDLK_d:    cam[0] -= 50*tim; break;
        case SDLK_a:    cam[0] += 50*tim; break;
        case SDLK_q:    cam[2] += 50*tim; break;
        case SDLK_e:    cam[2] -= 50*tim; break;
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



   	while(true) {
		static int  tt = SDL_GetTicks();
		int t = tt;
		tt = SDL_GetTicks();
		tim = (tt - t)/1;
		c.setMovementIntensity(tim);
		c.setRotationIntensity(tim/100);
        processEvents();
 
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
		c.refresh();
		/*glRotatef(rot[0], 1, 0, 0);
		glRotatef(rot[1], 0, 1, 0);
		glRotatef(rot[2], 0, 0, 1);
		glTranslatef(pos[0], pos[1], pos[2]);
		*/float fl[3];
		pos.get(fl);
		glLightfv(GL_LIGHT1, GL_POSITION, fl);
		Vector3 v1 = cam;
		v1[0] -= 100;
		Vector3 v2 = cam;
		v2[0] += 100;
		Vector3 v3 = cam;
		v3[1] += 100;

		/*Vector3 posneg = pos;
		posneg[0] = -posneg[0];
		posneg[1] = -posneg[1];
		posneg[2] = -posneg[2];
		map.draw(posneg);
*/
		map.draw();

		/*map.draw(cam);
		glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			float f1[3];
			float f2[3];
			float f3[3];
			v1.get(f1);
			v2.get(f2);
			v3.get(f3);
			lVertex3fv(f1);
			glVertex3fv(f2);
			glVertex3fv(f3);

		glEnd();
*/
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
	GLfloat diffuse[] = {1, 1, 0, 1};
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

	//map.load((char*)"data/map/maps/q3shw18.bsp");
	//map.load((char*)"data/map/maps/minirazz.bsp");
	//map.load((char*)"data/map/maps/csq3sg1.bsp");
	map.load((char*)"data/map/maps/artefacts1.bsp");
	//map.load((char*)"data/map/maps/20kdm2.bsp");

    mainLoop();
    return 0;
}
