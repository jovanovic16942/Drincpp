#include "Tankard.h"
#include <cmath>
#include "Global.h"

void Tankard::init()
{
	r = 0.07;
	h = 0.2;
	lvl = 0;
	state = idle;
	foam = 0;
	loadModel("Models/tankard.obj");
}

float Tankard::getR()
{
	return r;
}

float Tankard::getLvl()
{
	return lvl;
}

float Tankard::getH()
{
	return h;
}

tankardState Tankard::getState()
{
	return state;
}


void Tankard::setState(tankardState s)
{
	state = s;
}

void Tankard::setColor(colorMaterial color)
{
	this->color = color;
}

void Tankard::interact()
{
	if(touchedObject == this && heldObject == nullptr && state == idle){
		heldObject = this;
		state = taken;
		setPos((vector3f){10, 10, 10});
	}
	
}

void Tankard::update()
{
	if(state == idle || state == taken){
		lvl = 0;
		foam = 0;
	}else if(state == filling){
		if(lvl >= h - h/6){
			lvl = h - h/6;
			state = full;
		}
		lvl += 0.005 / r * deltaTime;
		foam += 0.001 / r * deltaTime;
	}
}

bool Tankard::collision(vector3f v)
{	
	bool collided = false;

	vector3f pos = getPos();
	float d = sqrt( (v.x - pos.x)*(v.x - pos.x) + (v.z - pos.z)*(v.z - pos.z) );	
	
	// test if player is touching this object (close enough for interaction)
	if(d <= h && state == idle){
		touchedObject = this;
	}else if(touchedObject == this){
		touchedObject = nullptr;
	}

	// test if player collided with this object
	if(d <= h && state == idle){
		collided = true;
	}	

	return collided;
}

void Tankard::draw()
{

	glPushMatrix();
	
	glTranslatef(getPos().x, getPos().y, getPos().z);

	if(state == idle){
		glTranslatef(0, -h/2, 0);
		glRotatef(90, 0, 0, -1);
		glRotatef(90, 0, 1, 0);
	}

	if(state != taken){ // draw only if tankard is not taken by the player

		glPushMatrix();
		glRotatef(90, 1, 0, 0);	
		glEnable(GL_COLOR_MATERIAL);
		setColorMaterial(color);
		if(lvl > 0){
			// draw the beer inside
			glTranslatef(0, 0, h-0.01);
			glRotatef(180, 1, 0, 0);
			gluCylinder(quad, r, r, lvl, 20, 1);
			glTranslatef(0, 0, lvl);
			gluDisk(quad, 0, r, 20, 1);
			// draw the foam
			glColor3f(1, 1, 1);
			gluCylinder(quad, r, r, foam, 20, 1);	
			glTranslatef(0, 0, foam);	
			gluDisk(quad, 0, r, 20, 1);
		}
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();

		// lastly draw the tankard itself
		glTranslatef(0, -h, 0);
		glScalef(0.4, 0.4, 0.4);
		setMaterial(glass);
		drawModel();
	}
	glPopMatrix();
}
