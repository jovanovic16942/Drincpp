#ifndef _DRINC_GLOBAL_H_
#define _DRINC_GLOBAL_H_

#include <cmath>
#include <time.h>
#include "Camera.h"
#include "TapMachine.h"
#include "Tavern.h"
#include "Tankard.h"
#include "Bar.h"
#include "Table.h"
#include <GL/glut.h>

extern int windowWidth, windowHeight; // Window dimensions

// Game objects
extern UsableObject * touchedObject; // Object player can interact with
extern UsableObject * heldObject; // Object player holds in his hand

extern Tavern tavern; // Game world object (tavern)
extern Camera gameCamera; // Camera object (Player)
extern direction dir; // Direction for camera movement
extern TapMachine tap, tap1, tap2; // Tap machines
extern Tankard tankard; // Tankard
extern Bar bar; // Bar
extern Table table1, table2, table3, table4, table5, table6; // Tables

extern GLUquadric* quad; // Needed for drawing cylinders and disks

extern float drunkness; // Blood-alcohol level

// Time variables
extern float deltaTime; // Time between frames
static int initialTime = time(nullptr), finalTime, frameCount = 0;
static float currentTime, lastTime;

// Speed variables
static const float movementSpeed = 2.5; // Camera movement speed
static const float rotationSpeed = M_PI/180*0.03; // Camera rotation speed
static const float leverRotationSpeed = 150; // Tap machine handle rotation speed
static const float barDoorSpeed = 150; // Door rotation speed

extern float awakeness; // Used for waking up animation

// Textures
extern GLuint names[1];

// Lighting
static GLfloat lightPosition[] = {0, 2, 0, 1};
static GLfloat lightAmbient[] = {0.4, 0.4, 0.4};
static GLfloat lightDiffuse[] = {0.8, 0.8, 0.8};
static GLfloat lightSpecular[] = {1, 1, 1};


// Materials and colors

// Beer 
static GLfloat beerColorPale[] = {0.8, 0.5, 0, 0.3};
static GLfloat beerColorRed[] = {0.3, 0.1, 0.05, 0.6};
static GLfloat beerColorDark[] = {0.06, 0.03, 0.03, 0.8};

// Wood
static GLfloat woodAmbient[] = {0.04, 0.035, 0.01, 1};
static GLfloat woodDiffuse[] = {0.045, 0.04, 0.02, 1};
static GLfloat woodSpecular[] = {0, 0, 0, 1}; 
static GLfloat woodShininess = 0; 

// Wood1
static GLfloat wood1Ambient[] = {0.020, 0.015, 0, 1};
static GLfloat wood1Diffuse[] = {0.015, 0.01, 0, 1};
static GLfloat wood1Specular[] = {0, 0, 0, 1}; 
static GLfloat wood1Shininess = 0; 


// Wall
static GLfloat wallAmbient[] = {0.4, 0.35, 0.25, 1};
static GLfloat wallDiffuse[] = {0.25, 0.2, 0.15, 1};
static GLfloat wallSpecular[] = {0.1, 0.1, 0.1, 1}; 
static GLfloat wallShininess = 0; 

// Glass
static GLfloat glassAmbient[] = {0.3,  0.3, 0.3, 0.1};
static GLfloat glassDiffuse[] = {0.3,  0.3, 0.3, 0.1};
static GLfloat glassSpecular[] = {0.3,  0.3, 0.3, 0.1}; 
static GLfloat glassShininess = 50; 

// Metal
static GLfloat metalAmbient[] = {0.3, 0.3, 0.3, 1};
static GLfloat metalDiffuse[] = {0.55, 0.55, 0.55, 1};
static GLfloat metalSpecular[] = {1, 1, 1, 1}; 
static GLfloat metalShininess = 100;

#endif
