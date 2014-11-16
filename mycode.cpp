#include <glut.h>
#include <iostream>
#include <GL\glext.h>
#include <atlimage.h>
#include <fstream>
#include<iostream>
#include <stdio.h>

using namespace std;

#include"light.h"
#include"object.h"
#include"texture.h"


GLsizei wh = 500, ww = 500;

Wall wall;
Tellurion tellurion;
Vase vase;
Table table;
Dragon dragon;

double view[3] = { 0.5, 0.5, 2 };
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	gluLookAt(view[0], view[1], view[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	light_init();
	glEnable(GL_TEXTURE_2D);
	tellurion.draw_tellution();
	vase.draw_vase();
	wall.wall();
	glDisable(GL_TEXTURE_2D);//close the texture map or it will map to other object
	
	table.draw_table();
	dragon.draw_dragon();
	lamp();
	
	//draw shadow
	tellurion.shadow();
	table.shadow();
	vase.shadow();
	dragon.shadow();
	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{

	
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, w / h, 0.1, 20);
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void mySpecial(int key, int x, int y){
	switch (key)
	{
	case GLUT_KEY_UP:
		light_position[1] += 0.1; 
		break;

	case GLUT_KEY_DOWN:
		light_position[1] -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		light_position[0] -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		light_position[0] += 0.1;
		break;

	case GLUT_KEY_F1:
		light_position[2] += 0.1;
		break;
	case GLUT_KEY_F2:
		light_position[2] -= 0.1;
		break;
	}
	
	printf("light_position %f %f %f\n",light_position[0],light_position[1],light_position[2]);
    glutPostRedisplay();
}

void keytest(unsigned char k, int x, int y){
	if (k == 'w')view[0] += 0.1;
	if (k == 's')view[0] -= 0.1;
	if (k == 'a')view[1] -= 0.1;
	if (k == 'd')view[1] += 0.1;
	if (k == 'j')view[2] -= 0.1;
	if (k == 'k')view[2] += 0.1;
	
	printf("view %lf %lf %lf\n", view[0], view[1], view[2]);
	glutPostRedisplay();
}


int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);
	texture_init();

	dragon.get_dragon();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(mySpecial);
	glutKeyboardFunc(keytest);
	glutMainLoop();
	
	return 0;
}

