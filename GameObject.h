#ifndef _DRINC_GAMEOBJECT_H_
#define _DRINC_GAMEOBJECT_H_

#include "GL/glut.h"
#include "vector3f.h"
#include "Light.h"
#include <vector>
#include "triangle.h"

using namespace std;

class GameObject
{
	public:
		GameObject(vector3f v) { setPos(v);}
		GameObject(float x, float y, float z) {setPos(x, y, z);}
		GameObject() {setPos((vector3f){0,0,0});}
		
		// Position getter and setters
		void setPos(vector3f v);
		void setPos(float x, float y, float z);
		vector3f getPos();

		// virtual function that every subclass must implement
		virtual bool collision(vector3f v) = 0; // returns true if v collides with the object
		virtual void draw() = 0; // draw the object

		bool loadModel(const char* path); // load the model
		void drawModel();  // draw the model

	private:
		vector3f pos; // Coordinates of the object
		vector<triangle> model; // Object model - vector of triangles
};


#endif
