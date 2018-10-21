#ifndef _DRINC_TAPMACHINE_H_
#define _DRINC_TAPMACHINE_H_

#include "UsableObject.h"
#include "Tankard.h"

enum tapState {noTankard, emptyTankard, pullHandle, pourDrink, releaseHandle}; // state of the tap machine

class TapMachine: public UsableObject
{
	public:
		TapMachine(vector3f v, colorMaterial color) : UsableObject(v), color(color) { init(); }

		void draw();
		void update();
		bool collision(vector3f v);
		void interact();
	private:
		void init();
		float phi; // angle of the handle
		Tankard* tankard; // pointer to tankard object that is in this objects slot
		tapState state;
		float d; // this will simulate flow of drink
		const colorMaterial color; // color of the beer
};

#endif
