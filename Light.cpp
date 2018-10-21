#include "Light.h"
#include "Global.h"

void initLight()
{
	// Enable lighting
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);
    	glEnable(GL_LIGHT0);
    	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

void setColorMaterial(colorMaterial color)
{
	switch(color){
			case pale:
				glColor4f(beerColorPale[0], beerColorPale[1], beerColorPale[2], beerColorPale[3]);
				break;
			case red:
				glColor4f(beerColorRed[0], beerColorRed[1], beerColorRed[2], beerColorRed[3]);
				break;
			case dark:
				glColor4f(beerColorDark[0], beerColorDark[1], beerColorDark[2], beerColorDark[3]);
				break;
		}
}

void setMaterial(material m)
{

	switch(m){

		case wood:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, woodAmbient);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, woodDiffuse);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, woodSpecular);
    		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, woodShininess);
			break;
		

		case wood1:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wood1Ambient);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wood1Diffuse);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wood1Specular);
    		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wood1Shininess);
			break;

		case wall:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wallAmbient);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wallDiffuse);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wallSpecular);
    		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, wallShininess);
			break;

		case metal:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, metalAmbient);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, metalDiffuse);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, metalSpecular);
    		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, metalShininess);
			break;

		case glass:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glassAmbient);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glassDiffuse);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glassSpecular);
    		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, glassShininess);
			break;
	}

}