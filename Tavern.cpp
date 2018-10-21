#include "Tavern.h"
#include "Global.h"

void Tavern::draw()
{
	glPushMatrix();
	glTranslatef(0, 0.7, 1.25);
	glScalef(1, 0.25, 0.75);
	setMaterial(wall);

	// Textured walls
	glBindTexture(GL_TEXTURE_2D, names[0]);
	glPushMatrix();
	glTranslatef(-5, -5, 5);
	glScalef(10, 10, 10);
	glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(12, 0);
        glVertex3f(1, 0, 0);

        glTexCoord2f(12, 6);
        glVertex3f(1, 1, 0);

        glTexCoord2f(0, 6);
        glVertex3f(0, 1, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-5, -5, -5);
	glScalef(10, 10, 10);
	glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(12, 0);
        glVertex3f(1, 0, 0);

        glTexCoord2f(12, 6);
        glVertex3f(1, 1, 0);

        glTexCoord2f(0, 6);
        glVertex3f(0, 1, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
	glTranslatef(-5, -5, 5);
	glScalef(10, 10, 10);
	glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(12, 0);
        glVertex3f(1, 0, 0);

        glTexCoord2f(12, 6);
        glVertex3f(1, 1, 0);

        glTexCoord2f(0, 6);
        glVertex3f(0, 1, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
	glTranslatef(-5, -5, -5);
	glScalef(10, 10, 10);
	glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(12, 0);
        glVertex3f(1, 0, 0);

        glTexCoord2f(12, 6);
        glVertex3f(1, 1, 0);

        glTexCoord2f(0, 6);
        glVertex3f(0, 1, 0);
    glEnd();
    glPopMatrix();



	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	// Floor
	glNormal3f(1, 0, 0);
	glColor3f(0.1, 0.07, 0.06);
	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(90, 1, 0, 0);
	glRectf(-gridSize/2, -gridSize/2, gridSize/2, gridSize/2);
	glPopMatrix();
	

	// Ceiling
	glNormal3f(-1, 0, 0);
	glColor3f(0.1, 0.07, 0.06);
	glPushMatrix();
	glTranslatef(0, 1.8, 0);
	glRotatef(90, 1, 0, 0);
	glRectf(-gridSize/2, -gridSize/2, gridSize/2, gridSize/2);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

bool Tavern::collision(vector3f v)
{
	bool collided = false;
	
	if(v.x >= gridSize/2 - 0.1 || v.x <= -gridSize/2 + 0.1 || v.z <= -gridSize/2 + 2.5 + 0.1 || v.z >= gridSize/2 - 0.1){
		collided = true;
	} 

	return collided;
}
