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
float transup = -50.0;
float rotfact;
Vector3 mr(0,0,0);
Vector3 mp(0,0,0);
Vector3 posm2(-150, 0, -600);

Model* model;
bool mode = true;
MS3DModel* model2;

MS3DModel mo;

// Kill program
void endProgram(int code) {
	delete  model;
	delete  model2;
	SDL_Quit();
	exit(code);
	}
 
// Handle SDL keypresses
void handleKeys(SDL_keysym* keysym, bool state) {
    if(state)switch(keysym->sym) {
        case SDLK_ESCAPE:    endProgram(0); break;
        case SDLK_DOWN:    trans -= 50; break;
        case SDLK_UP:    trans += 50; break;
        case SDLK_PAGEDOWN:    transup -= 10; break;
        case SDLK_PAGEUP:    transup += 10; break;
        case SDLK_RIGHT:    rotfact += 1; break;
        case SDLK_LEFT:    rotfact -= 1; break;
        case SDLK_s:    model->start(); break;
        case SDLK_a:    model->stop(); break;
        case SDLK_d:    model->pause(); break;
        case SDLK_q:    mode = !mode; break;
        case SDLK_i:    {mr[0]++; model->setRotation(mr);break;}
        case SDLK_k:    {mr[0]--; model->setRotation(mr);break;}
        case SDLK_l:    {mr[1]++; model->setRotation(mr);break;}
        case SDLK_j:    {mr[1]--; model->setRotation(mr);break;}
        case SDLK_o:    {mr[2]++; model->setRotation(mr);break;}
        case SDLK_u:    {mr[2]--; model->setRotation(mr);break;}
        case SDLK_KP6:    {mp[0]++; model->setPosition(mp);break;}
        case SDLK_KP4:    {mp[0]--; model->setPosition(mp);break;}
        case SDLK_KP8:    {mp[1]++; model->setPosition(mp);break;}
        case SDLK_KP2:    {mp[1]--; model->setPosition(mp);break;}
        case SDLK_KP7:    {mp[2]++; model->setPosition(mp);break;}
        case SDLK_KP9:    {mp[2]--; model->setPosition(mp);break;}
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
		int asd = 1;
   	while(true) {
        processEvents();
 
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
		glTranslatef(0.0, transup, trans);
		glRotatef(rotfact, 0,1,0);

		if(mode)
			model->draw();
		else
			((MS3DModel*)model)->drawSkeleton();

		model2->draw();
		Vector3 v = model2->getPosition();
		v[2] += asd*2;
		model2->setPosition(v);
		if(v[2] >= 300){
			asd = 0;
			Vector3 vr = model2->getRotation();
			vr[1]++;
			model2->setRotation(vr);
			if(vr[1] == 180)
				asd = -1;
		}
		if(v[2] <= posm2[2]){
			asd = 0;
			Vector3 vr = model2->getRotation();
			vr[1]++;
			if(vr[1] == 360){
				vr[1] = 0;
				asd = 1;
			}
			model2->setRotation(vr);
		}

		mo.draw();

		glBegin(GL_TRIANGLES);
			glVertex3f(-3, 0, 0);
			glVertex3f(3, 0, 0);
			glVertex3f(0, 3, 0);
		glEnd();

        SDL_GL_SwapBuffers();
    }
}
void setupOpengl() {
    glViewport(0, 0, width, height);
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
    glEnable( GL_BLEND );
	SDL_EnableKeyRepeat( 100, SDL_DEFAULT_REPEAT_INTERVAL );

}
 
// Init everything
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(width, height, 24, SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
    setupOpengl();

	model = new MS3DModel((char*)"data/beast.ms3d");
	//model = new MS3DModel((char*)"data/cat.ms3d");
	//model = new MS3DModel((char*)"data/model.ms3d");
	//model = new MS3DModel((char*)"data/fighter/fighter1.ms3d");
	try{
		model->load();
	}catch(exception &e){cout << e.what() << endl;}
	model->setAnimationInterval(0, model->getMaxFrames());
	//model->useTexture(false);
	//model->setAnimationInterval(0, 24);

	model2 = new MS3DModel((char*)"data/beast.ms3d");
	try{
		model2->load();
	}catch(exception &e){cout << e.what() << endl;}
	model2->setPosition(posm2);
	model2->setAnimationInterval(0, 24);
	model2->start();

	try{
		mo.load((char*)"data/cat.ms3d");
	}catch(exception &e){cout << e.what() << endl;}

    mainLoop();
    return 0;
}
