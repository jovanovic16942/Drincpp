#include "Table.h"
#include "Global.h"

void Table::draw()
{

	glPushMatrix();
	setMaterial(wood1);
	glTranslatef(getPos().x, getPos().y, getPos().z);
	glScalef(0.4, 0.3, 0.4);
	drawModel();

	glPopMatrix();

}

bool Table::collision(vector3f v)
{
	bool collided = false;

	vector3f pos = getPos();
	float d = sqrt( (v.x - pos.x)*(v.x - pos.x) + (v.z - pos.z)*(v.z - pos.z) );	
	

	// test if player collided with this object
	if(d <= 0.75){
		collided = true;
	}	

	return collided;
}