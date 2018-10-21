#ifndef _DRINC_TABLE_H_
#define _DRINC_TABLE_H_

#include "GameObject.h"

class Table: public GameObject
{
	public:
		Table(vector3f v) : GameObject(v) {loadModel("Models/table.obj");}
		Table(float x, float y, float z) : GameObject(x, y, z) {loadModel("Models/table.obj");}

		void draw();
		bool collision(vector3f v);
};

#endif