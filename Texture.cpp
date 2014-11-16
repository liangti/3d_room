#include<gl\glut.h>
#include<gl\glext.h>
#include"texture.h"
#include<atlimage.h>

GLfloat texpts[2][2][2] = { { { 0, 0 }, { 0, 1 } },
{ { 1, 0 }, { 1, 1 } } };
GLuint  texture[5];
GLuint ATLLoadTexture(const char *fileName)
{
	BITMAP bm;
	GLuint idTexture = 0;
	CImage img;				//需要头文件atlimage.h
	HRESULT hr = img.Load(fileName);
	if (!SUCCEEDED(hr))	//文件加载失败
	{
		MessageBox(NULL, "文件加载失败", "ERROR", 0);
		return NULL;
	}
	HBITMAP hbmp = img;
	if (!GetObject(hbmp, sizeof(bm), &bm))
		return 0;

	glGenTextures(1, &idTexture);
	if (idTexture)
	{
		glBindTexture(GL_TEXTURE_2D, idTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glPixelStoref(GL_PACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, bm.bmWidth, bm.bmHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bm.bmBits);	//这里不是GL_RGB
	}
	return idTexture;
}




void texture_init()
{

	glClearColor(0, 0, 0, 0.0); //Clear color specified 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//开启纹理映射
	//将bmp文件转换成纹理映射
	texture[0] = ATLLoadTexture("wall.bmp");
	texture[1] = ATLLoadTexture("tellurion.bmp");
	texture[2] = ATLLoadTexture("vase.bmp");
	texture[3] = ATLLoadTexture("ceiling.bmp");
	texture[4] = ATLLoadTexture("flood.bmp");
}
