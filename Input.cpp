#include <GL/glut.h>

#include "Global.h"
#include "Input.h"

void onKeyDown(unsigned char key, int x, int y)
{
	// Controls in readme file
	switch (key) {
		case 27:
			exit(0);
			break;
		case 'd':
		case 'D':
			dir = right;
			break;
		case 's':
		case 'S':
			dir = backwards;
			break;
		case 'a':
		case 'A':
			dir = left;
			break;
		case 'w':
		case 'W':
			dir = forwards;
			break;
		case 'f':
		case 'F':
			if(touchedObject != nullptr && drunkness < 3){
				touchedObject->interact();
			}
			break;		
		case 32:
			gameCamera.standUp();
			break;
    	}
}

void onKeyUp(unsigned char key, int x, int y)
{
	switch (key) {
		case 'd':
		case 'D':
			if(dir == right) dir = none;
			break;
		case 's':
		case 'S':
			if(dir == backwards) dir = none;
			break;
		case 'a':
		case 'A':
			if(dir == left) dir = none;
			break;
		case 'w':
		case 'W':
			if(dir == forwards) dir = none;
			break;
    	}
}

void onMouseMotion(int x, int y)
{
	static bool justWarped = false;	 // Doesnt work without this
	// taken from some code found on the internet
	if(justWarped){
		justWarped = false;
		return;
	}
	
	// if mouse moved from the center of the screen rotate the camera	
	
	int dx = x - windowWidth/2;
	int dy = y - windowHeight/2;

	if(dx)
		gameCamera.rotateYaw(dx);
	if(dy)
		gameCamera.rotatePitch(dy);
	
	glutWarpPointer(windowWidth/2, windowHeight/2); // move pointer to center of the screen
	justWarped = true;
}

