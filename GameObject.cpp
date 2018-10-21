#include "GameObject.h"

#include <fstream>
#include <iostream>
#include <sstream>

void GameObject::setPos(vector3f v)
{
	pos.x = v.x;
	pos.y = v.y;
	pos.z = v.z;
}

void GameObject::setPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

vector3f GameObject::getPos()
{
	vector3f vec;
	vec.x = pos.x;
	vec.y = pos.y;
	vec.z = pos.z;
	return vec;
}


bool GameObject::loadModel(const char* path)
{
	// Open the model file
	ifstream file;
	file.open(path);
	string line;

	if(!file.is_open()){
    	printf("Failed to open the file!\n");
    	return false;
	}

	// vectors that hold data read from file
	vector<vector3f> tmpVert;
	vector<vector3f> tmpNorm;

	// read file line by line
	while(getline(file, line)){

		istringstream iss(line);
		string flag;
		iss >> flag;

		// if line begins with 'v', it describes a vertex
		if(!flag.compare("v")){

			vector3f tv;
			iss >> tv.x >> tv.y >> tv.z;
			tmpVert.push_back(tv);

		// if line begins with 'vn', it describes a normal
		}else if(!flag.compare("vn")){

			vector3f tn;
			iss >> tn.x >> tn.y >> tn.z;
			tmpNorm.push_back(tn);

		// if line begins with 'f', it describes a face(triangle)
		}else if(!flag.compare("f")){
			// create a triangle using data read from file
			triangle tt;
			int v1i, v2i, v3i, n1i, n2i, n3i;
			char c;
			iss >> v1i >> c >> c >> n1i >> v2i >> c >> c >> n2i >> v3i >> c >> c >> n3i;
			tt.v1 = tmpVert[v1i-1];
			tt.v2 = tmpVert[v2i-1];
			tt.v3 = tmpVert[v3i-1];
			tt.n1 = tmpNorm[n1i-1];
			tt.n2 = tmpNorm[n2i-1];
			tt.n3 = tmpNorm[n3i-1];
			// add triangle to GameObject::model
			model.push_back(tt);
		}

	}

	file.close();
	return true;

}
void GameObject::drawModel()
{
	// draw the model triangle by triangle
	glBegin(GL_TRIANGLES);
	for(int i=0; i<model.size(); i++){
		glNormal3f(model.at(i).n1.x, model.at(i).n1.y, model.at(i).n1.z);
		glVertex3f(model.at(i).v1.x, model.at(i).v1.y, model.at(i).v1.z);
		glNormal3f(model.at(i).n2.x, model.at(i).n2.y, model.at(i).n2.z);
		glVertex3f(model.at(i).v2.x, model.at(i).v2.y, model.at(i).v2.z);
		glNormal3f(model.at(i).n3.x, model.at(i).n3.y, model.at(i).n3.z);
		glVertex3f(model.at(i).v3.x, model.at(i).v3.y, model.at(i).v3.z);
	}

	glEnd();

}
