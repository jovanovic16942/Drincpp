#ifndef _DRINC_CAMERA_H_
#define _DRINC_CAMERA_H_

#include "vector3f.h"

enum direction {none, forwards, backwards, left, right}; // Enum for camera movement direction

class Camera
{
	public:
		Camera() { init(); } // Camera constructor

		void update();
		void move(); // Move function (calls walk() and strafe())

		void standUp(); // set standingUp
		void fall(); // Resets camera (calls init)
		
		// Rotation functions
		void rotateYaw(float angle);  
		void rotatePitch(float angle); 
		
		// setters
		void setPos(vector3f v);
		void setDir(vector3f v);
		void setUp(vector3f v);
		// getters
		vector3f getPos();
		vector3f getDir();
		vector3f getUp();

		void balanceUpVector(vector3f d, float speed); // simulates rotation around z-axis
		
	private:
		void init(); // initializes camera

		// movement functions
		void walk(float speed); //front-back
		void strafe(float speed); //left-right
		
		vector3f pos; // Camera position
		vector3f lookDir; // Vector of the direction camera is looking in
		vector3f up; // Up vector

		bool down; // Is player lying down or standing up
		bool standingUp; // Stand up animation
		float phi, theta; // Camera yaw and pitch angles

};

#endif
