#include "GL/glut.h"
#include <iostream>
#include "Global.h"
#include "Time.h"

using namespace std;

void onTimer(int value)
{
	if (value != 0)
		return;

	// Call timer and display functions
	calcTimeDiff();
	glutPostRedisplay();
	glutTimerFunc(1, onTimer, 0);
}

void displayFPS()
{
	// FPS counter
	frameCount++;
	finalTime = time(nullptr);
	if(finalTime - initialTime > 0){
		cout<<"FPS : " << frameCount / (finalTime - initialTime)<<endl;
		frameCount = 0;
		initialTime = finalTime;
	}
}

void calcTimeDiff()
{
	// Calculate delta time
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - lastTime) / 1000.f;
}
