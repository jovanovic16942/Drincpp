#ifndef _DRINC_TANKARD_H_
#define _DRINC_TANKARD_H_

#include "UsableObject.h"

enum tankardState {idle, taken, waiting, filling, full}; // state of the tankard

class Tankard: public UsableObject
{
	public:
		Tankard(vector3f v) : UsableObject(v) { init(); }
		Tankard(float x, float y, float z) : UsableObject(x, y, z) { init(); }

		// getters and setters
		float getR(); 
		float getH();
		float getLvl();
		tankardState getState();
		void setState(tankardState s);
		void setColor(colorMaterial color);

		bool collision(vector3f v);
		void draw();
		void update();
		void interact();
	private:
		void init();
		float r; // Radius of the tankard
		float h; // Height of the tankard
		float lvl; // Height of the drink in this tankard
		float foam; // Height of the foam
		tankardState state; // State of the tankard
		colorMaterial color; // Color of the beer inside
}; 

#endif
