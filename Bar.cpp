#include "Bar.h"
#include "Global.h"

void Bar::init()
{
	state = closed;
	phi = 0;
}

bool Bar::collision(vector3f v)
{
	bool collided = false;
	vector3f pos = getPos();
	
	// Collision with front of the bar
	if( (v.x <= pos.x + 3.5 && v.x >= pos.x - 3.75) && 
	    (v.y <= pos.y + 0.4 && v.y >= pos.y - 0.4) &&
	    (v.z <= pos.z + 0.35 && v.z >= pos.z - 0.35)){
		collided = true;
	}

	// Collision with side of the bar
	if( (v.x <= pos.x - 3 && v.x >= pos.x - 3.75) &&
	    (v.y <= pos.y + 0.4 && v.y >= pos.y - 0.4) &&
	    (v.z >= pos.z) ){
		collided = true;
	}
	
	// Collision with door
	if( (v.x <= pos.x - 2.9 && v.x >= pos.x - 3.85) &&
	    (v.y <= pos.y + 0.4 && v.y >= pos.y - 0.4) &&
	    (v.z <= pos.z + 1.75 && v.z >= pos.z + 1.35 ) ){
		if(state == open){
			collided = false;
		}
		touchedObject = this;
		if( (v.x < pos.x - 3 && v.x > pos.x - 3.75) && touchedObject == this ){
			touchedObject = nullptr;
		}
	}else if(touchedObject == this){
		touchedObject = nullptr;
	}

	return collided;
}

void Bar::draw(){
	
	glPushMatrix();
	glTranslatef(getPos().x, getPos().y - 0.35, getPos().z);
	setMaterial(wood1);
	// Bottom part
	glPushMatrix();
	glColor3f(0.15, 0.1, 0);		

	// Front part
	glPushMatrix();
	glScalef(7, 0.7, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	
	// Side part
	glPushMatrix();
	glTranslatef(-3.4, 0, 0.6);
	glRotatef(90, 0, 1, 0);
	glScalef(1.25, 0.7, 0.2);
	glutSolidCube(1);
	glTranslatef(-1.425, 0, 0);
	glutSolidCube(1);	
	glPopMatrix();
	
	glPopMatrix();

	// Upper part
	glPushMatrix();
	glColor3f(0.20, 0.15, 0);		

	// Front part
	glPushMatrix();
	glTranslatef(0, 0.375, 0);
	glScalef(7.3, 0.05, 0.5);
	glutSolidCube(1);
	glPopMatrix();
	
	// Bar door
	glPushMatrix();
	glTranslatef(-3.4, 0.4, 1.225);
	glRotatef(phi, -1, 0, 0);
	glTranslatef(0, -0.025, 0.25);
	glScalef(0.5, 0.05, 0.5);
	glutSolidCube(1);
	glPopMatrix();	
	
	// Side part
	glPushMatrix();
	glTranslatef(-3.4, 0.375, 0.6);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 0.05, 0.5);
	glPushMatrix();
	glTranslatef(-0.1375, 0, 0);
	glScalef(0.975, 1, 1);
	glutSolidCube(1);
	glPopMatrix();
	glScalef(1.25, 1, 1);
	glTranslatef(-1.425, 0, 0);
	glutSolidCube(1);	
	glPopMatrix();
	
	glPopMatrix();
	
	glPopMatrix();
}

void Bar::update()
{
	if(state == closed){
		phi = 0;
	}else if(state == opening){
		phi += barDoorSpeed * deltaTime;
		if(phi >= 90){
			state = open;
		}
	}else if(state == open){
		phi = 90;
	}else if(state == closing){
		phi -= barDoorSpeed * deltaTime;
		if(phi <= 0){
			state = closed;
		}
	}
}

void Bar::interact()
{
	if(state == closed){
		state = opening;
	}else if(state == open){
		state = closing;
	}
}
