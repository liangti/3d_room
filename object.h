#include<gl\glut.h>
extern GLfloat vertices[8][3];
extern GLfloat normal[6][3];


extern GLfloat vase_ver1[6][4][3];






void directionalLightShadow(double dx, double dy, double dz,
	double a, double b, double c, double d, GLfloat M[16]);


class Wall
{
public:
	void polygon(int a, int b, int c, int d);
	void cube(int in_or_out);
	void wall();
	void shadow();
};


class Table
{
public:
	void table();
	void table_leg();
	void draw_table();
	void shadow();
};

class Chair
{
public:
	void chair();
	void draw_chair();
	void shadow();
};

class Tellurion
{
public:
	void tellurion();
	void tellurion_holder();
	void draw_tellution();
	void shadow();
};

class Vase
{
public:
	void vase();
	void draw_vase();
	void shadow();
};

class Dragon
{
public:
	GLfloat dragon_v[25000][3];
	GLuint dragon_face[50000][3];
	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
	void get_dragon();
	void dragon_normal(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3);
	void draw_dragon();
	void shadow();
};