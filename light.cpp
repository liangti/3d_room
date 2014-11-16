#include<gl\glut.h>
#include"light.h"


GLfloat light_position[3] = { 0, 1, 0, };
GLfloat light_destination[3] = { 0, 0, 0 };
GLfloat light_direction[3];


void light_dir(){
	light_direction[0] = light_destination[0] - light_position[0];
	light_direction[1] = light_destination[1] - light_position[1];
	light_direction[2] = light_destination[2] - light_position[2];


}

void light_init()
{




	light_dir();
	glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);


	GLfloat globalambient[] = { .5, .5, .5, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalambient);

	//From the light
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);


	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 160.);



	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void lamp(){
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glTranslatef(-light_direction[0], -light_direction[1], -light_direction[2]);
	glutSolidSphere(0.05, 20, 20);
	glTranslatef(light_direction[0], light_direction[1], light_direction[2]);
	glEnable(GL_LIGHTING);
}