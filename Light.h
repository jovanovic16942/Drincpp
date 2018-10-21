#ifndef _DRINC_LIGHT_H_
#define _DRINC_LIGHT_H_

#include <GL/glut.h>

enum material{wood, wood1, glass, metal, wall};
enum colorMaterial{pale, red, dark};

void initLight();
void setMaterial(material m);
void setColorMaterial(colorMaterial color);

#endif