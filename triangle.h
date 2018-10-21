#ifndef _DRINC_TRIANGLE_H_
#define _DRINC_TRIANGLE_H_

#include "vector3f.h"

// Struct that represents a triangle 
// 3 vertices - v1 v2 v3
// 3 normals - n1 n2 n3

struct triangle
{
	vector3f v1;
	vector3f n1;
	vector3f v2;
	vector3f n2;
	vector3f v3;
	vector3f n3;
};

#endif