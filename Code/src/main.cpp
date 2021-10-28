#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include "solve.h"

using namespace std;
GLuint texture[3];//6 textures for 6 faces of the cube
GLfloat xRot, yRot, zRot;//control cube's rotation
//load the bitmap and convert it into a texture

Solve image;
int currentTime = 1;
void LoadGLTextures()
{
	char surface[width * height * 3];
	char around[width * L * 3];
	char bottom[width * height * 3];

	image.getImage(surface, around, bottom, currentTime%time);
	currentTime += 1;

	//int width11, height11, nrChannels;

	//unsigned char* data = stbi_load("surface.bmp", &width11, &height11, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width11, height11, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, surface);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//data = stbi_load("around.bmp", &width11, &height11, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width11, height11, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, L, 0, GL_RGB, GL_UNSIGNED_BYTE, around);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//data = stbi_load("surface.bmp", &width11, &height11, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width11, height11, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bottom);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


}
int init()
{
	glEnable(GL_TEXTURE_2D);
	image.init_data();
	glGenTextures(3, texture);
	LoadGLTextures();
	
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	xRot += 25.0f;
	yRot += 25.0f;





	return 1;
}
void display()
{
	LoadGLTextures();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	//glRotatef(45,1.0f,0.0f,0.0f);
	//glRotatef(45,0.0f,1.0f,0.0f);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	// Front Face 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -L * 1.0 / width, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -L * 1.0 / width, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, L * 1.0 / width, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, L * 1.0 / width, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	// Back Face 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -L * 1.0 / width, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, L * 1.0 / width, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, L * 1.0 / width, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -L * 1.0 / width, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	// Top Face 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, L * 1.0 / width, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, L * 1.0 / width, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, L * 1.0 / width, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, L * 1.0 / width, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	// Bottom Face 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -L * 1.0 / width, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -L * 1.0 / width, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -L * 1.0 / width, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -L * 1.0 / width, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	// Right face 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -L * 1.0 / width, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, L * 1.0 / width, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, L * 1.0 / width, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -L * 1.0 / width, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	// Left Face 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -L * 1.0 / width, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -L * 1.0 / width, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, L * 1.0 / width, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, L * 1.0 / width, -1.0f);
	glEnd();

	/*xRot += 0.3f;
	yRot += 0.4f;
	zRot += 0.5f;*/
	glutSwapBuffers();
}
void reshape(int w, int h1)
{
	if (0 == h1)
		h1 = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)w / (GLfloat)h1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
		xRot += 2.5f;
		glutPostRedisplay();
		break;
	case 'y':
		yRot += 2.5f;
		glutPostRedisplay();
		break;
	case 'z':
		zRot += 2.5f;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
void OnTimer(int value)
{
	display();

	glutTimerFunc(speed, OnTimer, 1);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3D Model");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(speed, OnTimer, 1);

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}