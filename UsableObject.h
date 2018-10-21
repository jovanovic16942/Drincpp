#ifndef _DRINC_USABLEOBJECT_H_
#define _DRINC_USABLEOBJECT_H_

#include "GameObject.h"


class UsableObject: public GameObject
{
	public:
		UsableObject(vector3f v) : GameObject(v) { }
		UsableObject(float x, float y, float z) : GameObject(x, y, z) { }
		UsableObject() : GameObject() { }

		virtual void interact() = 0;
		virtual void update() = 0;
};


#endif
