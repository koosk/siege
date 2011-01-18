#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>
#include"gunit/MS3DModel.h"
 
using namespace std;
using namespace siege::gunit;

GLuint width = 800;
GLuint height = 800;
float trans = -300.0;
float rotfact;

Model* model;
 

// Kill program
void endProgram(int code) {
	//TODO hiba javitasa
	//delete [] model;
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
   	while(true) {
        processEvents();
 
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
		glTranslatef(0.0, -50.0, trans);
		glRotatef(rotfact, 0,1,0);

		model->draw();

        SDL_GL_SwapBuffers();
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

	model = new MS3DModel((char*)"data/beast.ms3d");
	model->load();

    mainLoop();
    return 0;
}
