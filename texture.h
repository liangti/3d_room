#include <GL\glut.h>

extern GLuint  texture[5];
extern GLfloat texpts[2][2][2];

GLuint ATLLoadTexture(const char *fileName);
void texture_init();