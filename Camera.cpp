#include <math.h>
#include <GL/glut.h>
#include "Camera.h"
#include "Global.h"

void Camera::init()
{
	vector3f vec;
	vec.x = 0;
	vec.y = -0.4;
	vec.z = 0;
	setPos(vec);
	vec.z = 0;
	vec.x = -1;
	vec.y = 0;
	setUp(vec);
	phi = 90;
	theta = 0;
	down = true;
	standingUp = false;
}

void Camera::fall()
{
	init();
}

void Camera::setPos(vector3f v)
{
	pos.x = v.x;
	pos.y = v.y;
	pos.z = v.z;
}

void Camera::setDir(vector3f v)
{
	lookDir.x = v.x;
	lookDir.y = v.y;
	lookDir.z = v.z;
}

void Camera::setUp(vector3f v)
{
	up.x = v.x;
	up.y = v.y;
	up.z = v.z;
}

vector3f Camera::getPos()
{
	vector3f vec;
	vec.x = pos.x;
	vec.y = pos.y;
	vec.z = pos.z;
	return vec;
}

vector3f Camera::getUp()
{
	vector3f vec;
	vec.x = up.x;
	vec.y = up.y;
	vec.z = up.z;
	return vec;
}

vector3f Camera::getDir(){
	vector3f vec;
	vec.x = lookDir.x;
	vec.y = lookDir.y;
	vec.z = lookDir.z;
	return vec;
}

void Camera::balanceUpVector(vector3f d, float speed)
{
		// simulate movement of the up vector from current to d
		// same as rotating camera around z-axis
		vector3f v = getUp();
		if(v.x == d.x && v.y == d.y && v.z == d.z){
			return;
		}else{

			if(v.x < d.x + 0.001 && v.x > d.x - 0.001)
				v.x = d.x;
			if(v.y < d.y + 0.001 && v.y > d.y - 0.001)
				v.y = d.y;
			if(v.z < d.z + 0.001 && v.z > d.z - 0.001)
				v.z = d.z;

			if(v.x > d.x + 0.001)
				v.x -= speed * deltaTime;
			if(v.y > d.y + 0.001)
				v.y -= speed * deltaTime;
			if(v.z > d.z + 0.001)
				v.z -= speed * deltaTime;

			if(v.x < d.x - 0.001)
				v.x += speed * deltaTime;
			if(v.y < d.y - 0.001)
				v.y += speed * deltaTime;
			if(v.z < d.z - 0.001)
				v.z += speed * deltaTime;

			setUp(v);
		}
}

void Camera::update()
{

	if(!standingUp && !down){

		// Check for colision and update camera	
		vector3f lastPos = getPos();	// Save last camera position
		move(); // Update camera position
		vector3f curPos = getPos();
		
		// if camera colides with any of the objects after movement, reset camera position
		if(tap.collision(curPos) || tap1.collision(curPos) || tap2.collision(curPos)
		   || tankard.collision(curPos)
		   || tavern.collision(curPos) || bar.collision(curPos) 
		   || table1.collision(curPos) || table2.collision(curPos) 
		   || table3.collision(curPos) || table4.collision(curPos) 
		   || table5.collision(curPos) || table6.collision(curPos)){
			setPos(lastPos);
		}
	}else if(standingUp){
		// simulate standing up
		vector3f v = getUp();
		if(v.x == 0 && v.y == 1 && v.z == 0){
			standingUp = false;
			down = false;
		}else{
			balanceUpVector((vector3f){0,1,0}, 1.2);

			v = getPos();
			if(v.y > 0.15){
				v.y = 0.15;			
			}

			if(v.y < 0.15){
				v.y += 1.2 * deltaTime;
			}

			setPos(v);
		}

	}


	// Update camera direction vector and set view matrix
	lookDir.x = cos(phi) * cos(theta);
	lookDir.y = sin(theta);
	lookDir.z = sin(phi) * cos(theta);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos.x,             pos.y,             pos.z,
		  	  pos.x + lookDir.x, pos.y + lookDir.y, pos.z + lookDir.z,
		  	  up.x,              up.y,              up.z );
}

void Camera::move()
{	
	switch(dir){
		case none: 
			return;
		case forwards:
			walk(movementSpeed * deltaTime);
			break;
		case backwards:
			walk(-movementSpeed/3 * deltaTime);
			break;
		case left:
			strafe(movementSpeed/2 * deltaTime);
			break;
		case right:
			strafe(-movementSpeed/2 * deltaTime);
			break;
	}
}

void Camera::walk(float speed)
{
	float lx = cos(phi);
	float lz = sin(phi);
	
	pos.x += speed * lx;
	pos.z += speed * lz;
}

void Camera::strafe(float speed)
{
	float lx = cos(phi - M_PI_2);
	float lz = sin(phi - M_PI_2);
	
	pos.x += speed * lx;
	pos.z += speed * lz;
}

void Camera::rotateYaw(float angle)
{
	phi += angle * rotationSpeed;

	if(down){ // Restrict camera movement when down
		const float limit = 89 * M_PI / 180;
		if(phi < 90-limit)
			phi = 90-limit;
		if(phi > 90 + limit/3)
			phi = 90 + limit/3;
	}
}

void Camera::rotatePitch(float angle)
{
	const float limit = 89 * M_PI / 180; // Strange things happen if its 90 degrees
	theta -= angle * rotationSpeed;
	
	// Limit pitch angle to about 90 degrees to add to realism
	if(theta < -limit)
		theta = -limit;
	if(theta > limit)
		theta = limit;

	if(down){ // Restrict camera movement when down
		if(theta < -limit/3)
			theta = -limit/3;
		if(theta > limit/3)
			theta = limit/3;
	}
}

void Camera::standUp()
{
	if(down)
		standingUp = true;
}
