#include "TapMachine.h"
#include "Global.h"

void TapMachine::init()
{
	phi = 90;
	state = noTankard;
	d = 0;
	tankard = nullptr;
}

void TapMachine::interact()
{
	if(state == noTankard && dynamic_cast<Tankard*>(heldObject) && tankard == nullptr){

		// Set tankard from hand to machine
		tankard = dynamic_cast<Tankard*>(heldObject);
		heldObject = nullptr;
		// Set tankard position		
		vector3f pos = getPos();
		pos.y -= 0.2;
		pos.z -= 0.2;
		tankard->setPos(pos);
		// Set tankard and machine state
		tankard->setState(waiting);
		state = emptyTankard;
		
	}else if(state == emptyTankard){
		// Pull lever
		state = pullHandle;

	}else if(heldObject == nullptr && tankard != nullptr && tankard->getState() == 4){
		// Take tankard and drink a beer
		heldObject = (UsableObject*)tankard;
		tankard->setState(taken);
		tankard = nullptr;
		drunkness += 0.667;
	}
}

void TapMachine::update()
{

	if(state == noTankard || state == emptyTankard){
		phi = 90;
	}else if(state == pullHandle){
		phi -= leverRotationSpeed * deltaTime;
		if(phi <= 0){
			state = pourDrink;
			tankard->setState(filling);
			tankard->setColor(color);
			phi = 0;
		}
	}else if(state == pourDrink){
		d = 2;
		if(tankard->getState() == full){
			state = releaseHandle;
			d = 0;
		}
	}else if(state == releaseHandle){
		phi += leverRotationSpeed * deltaTime;
		if(phi > 90){
			state = noTankard;
			phi = 90;
		}
	}
}

void TapMachine::draw()
{	
	glPushMatrix();

	glTranslatef(getPos().x, getPos().y, getPos().z);
	setMaterial(wood);
	//setMaterial(wood, GL_BACK);
	glPushMatrix();
	glColor3f(0.25, 0.2, 0.2);
	glScalef(2, 1, 1);
	glTranslatef(0, -0.6, -0.2);
	glutSolidCube(0.4);
	glPopMatrix();
	
	glPushMatrix();	
	
	glColor3f(0.1, 0.05, 0);
	gluCylinder(quad, 1, 1, 1.5, 20, 1);
	glRotatef(180, 0, 1, 0);
	gluDisk(quad, 0, 1, 20, 1);
	glRotatef(-180, 0, 1, 0);

	glColor3f(0.4, 0.4, 0.5);
	setMaterial(metal);
	glTranslatef(0, 0.2, -0.4);
	gluCylinder(quad, 0.1, 0.1, 0.4, 20, 1);
	glRotatef(180, 0, 1, 0);
	gluDisk(quad, 0, 0.1, 20, 1);
	glRotatef(-180, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0.2, 0);
	gluCylinder(quad, 0.02, 0.02, 0.3, 20, 1);



	// Drink
	glEnable(GL_COLOR_MATERIAL);
	setColorMaterial(color);
	glPushMatrix();
	if(state == pourDrink){
		glScalef(1, 1, d-3.5*tankard->getLvl());
		gluCylinder(quad, 0.017, 0.017, 0.3, 20, 1);
	}
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPopMatrix();

	// Movable handle
	glColor3f(0.05, 0.025, 0);
	setMaterial(wood);
	glTranslatef(0, 0.2, -0.41);
	glRotatef(phi, 0, 0, 1);
	glTranslatef(0, -0.1, 0);
	glScalef(0.2, 2, 0.2);
	glutSolidCube(0.1);

	glPopMatrix();
}


bool TapMachine::collision(vector3f v)
{
	bool collided = false;
	vector3f pos = getPos();
	
	// test if player is touching this object (close enough for interaction)
	if((v.x <= pos.x + 1.1 && v.x >= pos.x - 1.1) &&
	   //(v.y <= pos.y + 1 && v.y >= pos.y) 	  &&
	   (v.z <= pos.z && v.z >= pos.z - 1)){
		touchedObject = this;
	}else if(touchedObject == this){
		touchedObject = nullptr;
	}

	// test if player collided with this object
	if((v.x <= pos.x + 1.1 && v.x >= pos.x - 1.1) &&
	   //(v.y <= pos.y + 1 && v.y >= pos.y) 	  &&
	   (v.z <= pos.z + 1.6 && v.z >= pos.z - 0.5)){
		collided = true;
	}

	return collided;
}
