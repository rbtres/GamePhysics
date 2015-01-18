//============================================================================================
//Create by Robert Bethune
//Modified http://www2.cs.uregina.ca/~anima/408/Notes/Timelines/Controlling-the-Display-Rate.htm
//Also https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html
//Mouse Info http://www.zeuscmd.com/tutorials/glut/03-MouseInput.php
//Main.cpp
//Used for creating a cube and than updating for future project
//Creation Date 1/17/2015
//============================================================================================
#include <iostream>
#include <windows.h>

#include "GL/gl.h"
#include "GL/glut.h"
#include "GameApp.h"
#include "InputManager.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix.h"

using namespace std;
//--------------------------------------------------------------------------------------------
void idle();
void display();
void update();
void initialize();
void cleanup();
void mousePos(int x, int y);
void handleKeyDown(unsigned char key, int x, int y);
void handleKeyUp(unsigned char key, int x, int y);
void reshape(int width, int height);
void handleMouse(int button, int state, int x, int y);
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
const unsigned int TARGET_FPS = 60;
const double TIME_PER_FRAME = 1000.0 / TARGET_FPS;
int g_start_time;
int g_current_frame_number;

GameApp* gp_GameApp;

float positionz[10];
float positionx[10];
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	gp_GameApp = new GameApp();

	

	initialize();
	return 0;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void initialize()
{
	g_start_time = glutGet(GLUT_ELAPSED_TIME);
	g_current_frame_number = 0;

	glutInitWindowSize(720, 720);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Rotating Box Test");

	
	float lightPosition[] = { 100.0, 100.0, 100.0, 0 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader
	//glDepthFunc(GL_EQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	

	gp_GameApp->Init();

	atexit(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mousePos);
	glutMouseFunc(handleMouse);
	glutKeyboardFunc(handleKeyDown);
	glutKeyboardUpFunc(handleKeyUp);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void idle()
{
	double end_frame_time, end_rendering_time, waste_time;

	end_frame_time = g_start_time + (g_current_frame_number + 1) * TIME_PER_FRAME;
	end_rendering_time = glutGet(GLUT_ELAPSED_TIME);
	waste_time = end_frame_time - end_rendering_time;

	if (waste_time < 0.0)
	{
		update();
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void update()
{
	glutPostRedisplay();
	g_current_frame_number++;

	gp_GameApp->Update();
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(1 * g_current_frame_number, .45f, .45f, .45f);
	glutSolidCube(.25);
	glPopMatrix();

	glutSwapBuffers();
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void cleanup()
{
	gp_GameApp->CleanUp();
	delete gp_GameApp;
	gp_GameApp = NULL;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void mousePos(int x, int y)
{
	Vector2D mousePos = Vector2D((float)x, (float)y);
	gp_GameApp->HandleMouse(mousePos);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void handleKeyDown(unsigned char key, int x, int y)
{
	gp_GameApp->HandleKeyDown(key);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void handleKeyDown(unsigned char key, int x, int y)
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void handleMouse(int button, int state, int x, int y)
{
	gp_GameApp->HandleMouseDown(Vector2D(button, state),Vector2D(x,y));
}
//--------------------------------------------------------------------------------------------
void reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
//--------------------------------------------------------------------------------------------
