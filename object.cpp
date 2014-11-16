#include "Texture.h"
#include "object.h"
#include "light.h"
#include <gl\glut.h>
#include <fstream>
#include <stdio.h>

GLfloat vertices[8][3] = { { -1., -1., -1. }, { 1., -1., -1. }, { 1., 1., -1. },
{ -1., 1., -1. }, { -1., -1., 1. }, { 1., -1., 1. },
{ 1., 1., 1. }, { -1., 1., 1. } };

GLfloat normal[6][3] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { -1, 0, 0 }, { 0, -1, 0 }, { 0, 0, -1 } };


GLfloat vase_ver1[6][4][3] = { { { 1, 4, 0 }, { 0.5, 3, 0 }, { 2, 1, 0 }, { 1.5, 0, 0 } },
{ { 1, 4, 1 }, { 0.5, 3, 0.5 }, { 2, 1, 2 }, { 1.5, 0, 1.5 } },
{ { -1, 4, 1 }, { -0.5, 3, 0.5 }, { -2, 1, 2 }, { -1.5, 0, 1.5 } },
{ { -1, 4, -1 }, { -0.5, 3, -0.5 }, { -2, 1, -2 }, { -1.5, 0, -1.5 } },
{ { 1, 4, -1 }, { 0.5, 3, -0.5 }, { -2, 1, -2 }, { 1.5, 0, -1.5 } },
{ { 1, 4, 0 }, { 0.5, 3, 0 }, { 2, 1, 0 }, { 1.5, 0, 0 } }
};




void directionalLightShadow(double dx, double dy, double dz,
	double a, double b, double c, double d, GLfloat M[16]) {
	M[0] = b*dy + c*dz;  M[4] = -b*dx;  M[8] = -c*dx;  M[12] = -d*dx;
	M[1] = -a*dy;  M[5] = a*dx + c*dz;  M[9] = -c*dy;  M[13] = -d*dy;
	M[2] = -a*dz;  M[6] = -b*dz;  M[10] = a*dx + b*dy;  M[14] = -d*dz;
	M[3] = 0;        M[7] = 0;        M[11] = 0;  M[15] = a*dx + b*dy + c*dz;
}

void Wall::polygon(int a, int b, int c, int d){
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(vertices[a]);
	glTexCoord2f(0.0, 1.0);
	glVertex3fv(vertices[b]);
	glTexCoord2f(1.0, 1.0);
	glVertex3fv(vertices[c]);
	glTexCoord2f(1.0, 0.0);
	glVertex3fv(vertices[d]);
	glEnd();

}

void Wall::cube(int in_or_out){
	//out==1 and in==-1
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glNormal3d(0, -1.0*in_or_out, 0);
	polygon(2, 3, 7, 6);//top
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glNormal3f(0, 0, 1.0*in_or_out);
	polygon(0, 3, 2, 1);//back
	glNormal3f(1.0*in_or_out, 0, 0);
	polygon(4, 7, 3, 0);//left
	glNormal3f(-1.0*in_or_out, 0, 0);
	polygon(1, 2, 6, 5);//right

	if (in_or_out == -1){
		glNormal3f(0, 0, -1.0*in_or_out);
		polygon(4, 5, 6, 7);//forward
	}
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glNormal3f(0, 1.0*in_or_out, 0);
	polygon(0, 1, 5, 4);//bottom
}

void Wall::wall(){

		GLfloat earth_mat_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		GLfloat earth_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//FRONT_AND_
		//glBindTexture(GL_TEXTURE_2D, texture[2]);
		glPushMatrix();
		glScalef(1.5, 1.1, 1.1);
		cube(1);
		glPopMatrix();
	
}

void Table::table(){
	GLfloat diffuse[] = { .3, 0, 0, 1. };
	GLfloat specular[] = { 1, 1, 1, 1. };
	glMaterialfv(GL_FRONT, GL_AMBIENT, diffuse);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	glMaterialf(GL_FRONT, GL_SHININESS, 120);

	glEnable(GL_NORMALIZE);//define normal vector to solve the problem that cause by scalef function

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glScalef(0.7, 0.025, 0.6);
	glutSolidCube(2);
	glPopMatrix();
}

void Table::table_leg(){
	GLfloat diffuse[] = { .4, 0, 0, 1. };
	GLfloat specular[] = { .5, .5, .5, 1. };

	glMaterialfv(GL_FRONT, GL_AMBIENT, diffuse);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	glMaterialf(GL_FRONT, GL_SHININESS, 120.);

	glEnable(GL_NORMALIZE);//define normal vector to solve the problem that cause by scalef function

	glScalef(0.05, 0.25, 0.05);
	glutSolidCube(2);
	glScalef(20, 4, 20);
}

void Table::draw_table(){
	glTranslatef(-0.35, -0.75, -0.3);
	table_leg();
	glTranslatef(0.35, 0.75, 0.3);
	glTranslatef(0.35, -0.75, -0.3);
	table_leg();
	glTranslatef(-0.35, 0.75, 0.3);
	glTranslatef(-0.35, -0.75, 0.3);
	table_leg();
	glTranslatef(0.35, 0.75, -0.3);
	glTranslatef(0.35, -0.75, 0.3);
	table_leg();
	glTranslatef(-0.35, 0.75, -0.3);
	table();
}



void Table::shadow(){
	GLfloat M[16];

	glColor4f(0., 0., 0., 1.);
	glDisable(GL_LIGHTING);
	//table shadow
	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 0, 1, 0, 1.1, M);
	glMultMatrixf(M);
	draw_table();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 1, 0, 0, 1.5, M);
	glMultMatrixf(M);
	draw_table();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], -1, 0, 0, 1.5, M);
	glMultMatrixf(M);
	draw_table();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 0, 0, 1, 1.1, M);
	glMultMatrixf(M);
	draw_table();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 0, -1, 0, 1.1, M);
	glMultMatrixf(M);
	draw_table();
	glPopMatrix();

}

void Chair::chair(){
	glPushMatrix();
	glTranslatef(0.95, 0, 2.0);
	glScalef(0.05, 0.3, 0.2);
	glutSolidCube(2);					//back of chair
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, -0.35, 2.0);
	glScalef(0.3, 0.05, 0.2);
	glutSolidCube(2);					//seat
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -0.6, 1.9);
	glScalef(0.05, 0.2, 0.05);
	glutSolidCube(2);					//left back leg
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -0.6, 2.15);
	glScalef(0.05, 0.2, 0.05);
	glutSolidCube(2);						//left leg
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, -0.6, 1.9);
	glScalef(0.05, 0.2, 0.05);
	glutSolidCube(2);					//right leg
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, -0.6, 2.15);
	glScalef(0.05, 0.2, 0.05);
	glutSolidCube(2);
	glPopMatrix();

}

void Chair::draw_chair(){
	GLfloat earth_mat_ambient[] = { 0.3f, 0.f, 0.3f, 1.0f };
	GLfloat earth_mat_diffuse[] = { 0.3f, 0.f, 0.3f, 1.0f };
	GLfloat earth_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat earth_mat_shininess = 10.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

	glPushMatrix();
	glTranslatef(0.5,0,0);
	glScalef(0.4,0.4,0.4);
	chair();
	glPopMatrix();
}

void Tellurion::tellurion(){

	glBindTexture(GL_TEXTURE_2D, texture[1]);

	GLUquadricObj *quadObj = gluNewQuadric();//create a curve
	gluQuadricTexture(quadObj, GL_TRUE);        //enable the texture
	

	gluSphere(quadObj, 0.15, 20, 20); 
	gluDeleteQuadric(quadObj);


}

void Tellurion::tellurion_holder(){
	glPushMatrix();
	glTranslatef(-0.2, -0.5, -0.2);
	glScalef(0.2, 0.1, 0.2);
	glutSolidCube(1);				//地球仪底座
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, -0.4, -0.2);
	glScalef(0.04, 0.3, 0.04);
	glutSolidCube(1);			//地球仪支杆
	glPopMatrix();
}

void Tellurion::draw_tellution(){

	GLfloat earth_mat_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat earth_mat_diffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat earth_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat earth_mat_shininess = 30.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

	glPushMatrix();
	glTranslatef(-0.2, -0.2, -0.2);
	//glRotatef(90, 0, 1, 0);
	tellurion();
	glPopMatrix();

	tellurion_holder();
}

void Tellurion::shadow(){
	GLfloat M[16];

	glColor4f(0., 0., 0., 1.);
	glDisable(GL_LIGHTING);
	//table shadow

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 1, 0, 0, 1.5, M);
	glMultMatrixf(M);
	draw_tellution();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], -1, 0, 0, 1.5, M);
	glMultMatrixf(M);
	draw_tellution();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 0, 0, 1, 1.1, M);
	glMultMatrixf(M);
	draw_tellution();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 0, -1, 0, 0.55, M);//shadow on the table top 
	glMultMatrixf(M);
	draw_tellution();
	glPopMatrix();


}

void Vase::vase(){
	glBindTexture(GL_TEXTURE_2D, texture[2]);//new about texture

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, &vase_ver1[0][0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texpts[0][0][0]);//new about texture
	//激活二维求值器
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);//new about texture
	//自动生成曲面的法线
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);

	GLUquadricObj *quadObj = gluNewQuadric();//创建一个二次曲面物体
	gluQuadricTexture(quadObj, GL_TRUE);        //启用该二次曲面的纹理
	//绑定纹理
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 1, 0, 0);
	gluDisk(quadObj, 0, 1, 20, 20); //画圆
	gluDeleteQuadric(quadObj);
}

void Vase::draw_vase(){
	GLfloat earth_mat_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat earth_mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat earth_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat earth_mat_shininess = 30.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

	glPushMatrix();
	glTranslatef(0.2, -0.5, -0.2);
	glScalef(0.1, 0.1, 0.1);
	vase();
	glPopMatrix();
}

void Vase::shadow(){
	GLfloat M[16];

	glColor4f(0., 0., 0., 1.);
	glDisable(GL_LIGHTING);
	//table shadow

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 1, 0, 0, 1.5, M);
	glMultMatrixf(M);
	draw_vase();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], -1, 0, 0, 1.5, M);
	glMultMatrixf(M);
	draw_vase();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 0, 0, 1, 1.1, M);
	glMultMatrixf(M);
	draw_vase();
	glPopMatrix();

	glPushMatrix();
	directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 0, -1, 0, 0.55, M);//shadow on the table top 
	glMultMatrixf(M);
	draw_vase();
	glPopMatrix();
	

}

void Dragon::get_dragon(){
	FILE *rstream = fopen("dragon.obj", "r+");
	char txt[100];
	int vet, face;
	vet = face = 0;
	while (!feof(rstream)){
		fscanf(rstream, "%s", &txt);
		if (txt[0] == 'v'&&strlen(txt) == 1){
			fscanf(rstream, "%f %f %f", &dragon_v[vet][0], &dragon_v[vet][1], &dragon_v[vet][2]);
			//printf("%f %f %f\n", dragon_v[vet][0], dragon_v[vet][1], dragon_v[vet][2]);
			vet++;
		}
		if (txt[0] == 'f'&&strlen(txt) == 1){
			fscanf(rstream, "%u %u %u", &dragon_face[face][0], &dragon_face[face][1], &dragon_face[face][2]);
			//printf("%u %u %u\n", dragon_face[face][0], dragon_face[face][1], dragon_face[face][2]);
			face++;
		}
		if (face >= 50000 && vet >= 25000)break;
		//printf("%d %d\n",face,vet);
	}

}

void Dragon::dragon_normal(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3){
	nx = y1*z2 - y1*z3 - y2*z1 + y2*z3 + y3*z1 - y3*z2;
	ny = -x1*z2 + x1*z3 + x2*z1 - x2*z3 - x3*z1 + x3*z2;
	nz = x1*y2 - x1*y3 - x2*y1 + x2*y3 + x3*y1 - x3*y2;
	
}

void Dragon::draw_dragon(){
	GLfloat earth_mat_ambient[] = { 0.f, 0.5f, 0.5f, 1.0f };
	GLfloat earth_mat_diffuse[] = { 0.f, 0.5f, 0.5f, 1.0f };
	GLfloat earth_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat earth_mat_shininess = 30.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

	glEnable(GL_NORMALIZE);
	glPushMatrix();
	glTranslatef(0.2, -0.1, 0.55);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i<25000; i++){
		dragon_normal(dragon_v[dragon_face[i][0] - 1][0], dragon_v[dragon_face[i][0] - 1][1], dragon_v[dragon_face[i][0] - 1][2],
			dragon_v[dragon_face[i][1] - 1][0], dragon_v[dragon_face[i][1] - 1][1], dragon_v[dragon_face[i][1] - 1][2],
			dragon_v[dragon_face[i][2] - 1][0], dragon_v[dragon_face[i][2] - 1][1], dragon_v[dragon_face[i][2] - 1][2]);
		//printf("%d %d %d\n",nx,ny,nz);
		glNormal3d(nx, ny, nz);
		glVertex3fv(dragon_v[dragon_face[i][0] - 1]);
		glVertex3fv(dragon_v[dragon_face[i][1] - 1]);
		glVertex3fv(dragon_v[dragon_face[i][2] - 1]);
	}
	glEnd();
}

void Dragon::shadow(){
		GLfloat M[16];

		glColor4f(0., 0., 0., 1.);
		glDisable(GL_LIGHTING);
		//table shadow

		glPushMatrix();
		directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 1, 0, 0, 1.5, M);
		glMultMatrixf(M);
		draw_dragon();
		glPopMatrix();

		glPushMatrix();
		directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], -1, 0, 0, 1.5, M);
		glMultMatrixf(M);
		draw_dragon();
		glPopMatrix();

		glPushMatrix();
		directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 0, 0, 1, 1.1, M);
		glMultMatrixf(M);
		draw_dragon();
		glPopMatrix();

		glPushMatrix();
		directionalLightShadow(-light_direction[0], -light_direction[1], -light_direction[2], 0, -1, 0, 0.55, M);//shadow on the table top 
		glMultMatrixf(M);
		draw_dragon();
		glPopMatrix();


	
}