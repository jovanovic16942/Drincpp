#include <iostream>
#include <GL/glut.h>
#include <string>
#include <cstdlib>
#include "Camera.h"
#include "Global.h"
#include "Input.h"
#include "GameObject.h"
#include "TapMachine.h"
#include "Time.h"
#include "Tavern.h"
#include "Tankard.h"
#include "UsableObject.h"
#include "Bar.h"
#include "Light.h"
#include "Table.h"
#include "Image.h"

#define FILENAME0 "Textures/wall.bmp"

using namespace std;



// Declare functions
static void onReshape(int width, int height);
static void onDisplay(void);

void stateOfMind(float drunkness);

// Declare global variables and objects
int windowWidth, windowHeight;

UsableObject * touchedObject = nullptr; // Pointer to the object player can interact with
UsableObject * heldObject = nullptr; // Pointer to the object player holds in his hand

GLUquadric* quad;

Tavern tavern;
Bar bar;
Camera gameCamera;
direction dir;
TapMachine tap((vector3f){4, 0.2, 4}, pale);
TapMachine tap1((vector3f){2, 0.2, 4}, red);
TapMachine tap2((vector3f){0, 0.2, 4}, dark);
Tankard tankard((vector3f){0, -0.3, 1});
Table table1(3.5, -0.6, -1);
Table table2(1.5, -0.6, -0.5);
Table table3(-1.5, -0.6, -0.5);
Table table4(-3.5, -0.6, -1);
Table table5(-3.5, -0.6, 1.5);
Table table6(-3.5, -0.6, 3.5);

GLuint names[1];

float awakeness = 1;
float drunkness = 0;
/* 0 - sober
   1 - tipsy
   2 - drunk
   3 - pass out
   */

// Time variables
float deltaTime;

Image * image; // image file used in texture initialization

int main(int argc, char **argv)
{
	// GLUT init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);

	// Create window
	int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowSize(screenWidth * 0.8, screenHeight * 0.8);
	glutInitWindowPosition(screenWidth * 0.1, screenHeight * 0.1);
	glutCreateWindow(argv[0]);

	// Set callback functions
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);
	glutMotionFunc(onMouseMotion);
	glutPassiveMotionFunc(onMouseMotion);
	glutReshapeFunc(onReshape);
	glutDisplayFunc(onDisplay);

	// OpenGL init
	glClearColor(0.15, 0.15, 0.15, 0);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2);
    

	// TEXTURES
	glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_MODULATE);
    image = image_init(0, 0);

    // Create teture
    image_read(image, (char*)("Textures/wall.bmp"));
    glGenTextures(1, names);

 	glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    image_done(image);


	// Start the timer
	glutTimerFunc(1, onTimer, 0);

	// Hide cursor and move it to center of the screen    
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(windowWidth/2, windowHeight/2);
	
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	quad = gluNewQuadric();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();

	return 0;
}

static void onReshape(int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	// Set the viewport matrix
	glViewport(0, 0, windowWidth, windowHeight);


	// Set the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		60,
		windowWidth/(float)windowHeight,
		0.01, 50);
	glMatrixMode(GL_MODELVIEW);
}

static void onDisplay(void)
{

	// Clear the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Update camera
	gameCamera.update();

	// Update game objects
	tap.update();
	tap1.update();
	tap2.update();
	tankard.update();
	bar.update();

	// Update player state
	drunkness -= 0.01 * deltaTime;
	if(drunkness < 0){
		drunkness = 0;
	}
	if(drunkness > 3 && awakeness >= 1){
		drunkness = 0;
		gameCamera.fall();
		tankard.setPos(0.0f,-0.3f,1.0f);
		heldObject = nullptr;
		tankard.setState(idle);
		touchedObject = nullptr;
		awakeness = 1;
	}

	// Update light position
    initLight();

	// Draw objects
	tavern.draw();
	bar.draw();
	tap.draw();
	tap1.draw();
	tap2.draw();
	tankard.draw();
	table1.draw();
	table2.draw();
	table3.draw();
	table4.draw();
	table5.draw();
	table6.draw();

	
	stateOfMind(drunkness);

	//glutSwapBuffers();
	glFlush();	

	displayFPS();
	
}


void stateOfMind(float drunkness)
{
	// This should simulate waking up and losing consciousness
	if(awakeness != 1 || awakeness != 0){

		glDisable(GL_LIGHTING);
		glColor4f(0, 0, 0, awakeness);
		vector3f camPos = gameCamera.getPos();
		glTranslatef(camPos.x, camPos.y, camPos.z);
		glutSolidSphere(0.1, 20, 20);
		glEnable(GL_LIGHTING);

		if(awakeness < 1 && drunkness >= 3){
			awakeness += 1 * deltaTime;
		}else if(awakeness > 0){
			awakeness -= 0.5 * deltaTime;
		}
	}

	static bool changeUp = false;
	static vector3f camTo;

	
	if(drunkness <= 1 && drunkness > 0){

		gameCamera.balanceUpVector((vector3f){0, 1, 0}, 1.2);

	}
	// This will simulate effects of intoxication
	if(drunkness >= 1){

	vector3f camUp = gameCamera.getUp();
		
		if(camUp.x == 0 && camUp.y == 1 && camUp.z == 0){

			changeUp = true;
			
			camTo.x = (((float) rand() / (RAND_MAX)) * 2 - 1)/(3 - drunkness/2);
			camTo.y = 1 - (((float) rand() / (RAND_MAX)) * 2 - 1)/(3 - drunkness/2);
			camTo.z = (((float) rand() / (RAND_MAX)) * 2 - 1)/(3 - drunkness/2);

		}

		if(changeUp){
			gameCamera.balanceUpVector(camTo, 0.25);
			if(camUp.x == camTo.x && camUp.y == camTo.y && camUp.z == camTo.z){
				changeUp = false;
			}
		}else{
			gameCamera.balanceUpVector((vector3f){0, 1, 0}, 1);
		}

	}

}
