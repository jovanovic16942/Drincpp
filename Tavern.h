#ifndef _DRINC_TAVERN_H_
#define _DRINC_TAVERN_H_

#include "GameObject.h"

class Tavern: public GameObject
{
	public:
		bool collision(vector3f v);
		void draw();
	private:
		static const int gridSize = 10; // Size of the grid
}; 

#endif
