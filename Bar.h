#ifndef _DRINC_BAR_H_
#define _DRINC_BAR_H_

#include "UsableObject.h"

enum barState {closed, opening, open, closing}; // state of the bar door

class Bar: public UsableObject
{
	public:
		Bar() : UsableObject((vector3f){1.5, 0 ,2}) { init(); }

		void draw();
		void update();
		bool collision(vector3f v);
		void interact();
	private:
		void init();
		barState state;
		float phi; // angle of the door
};

#endif
