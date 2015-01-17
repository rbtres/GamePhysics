//============================================================================================
//Create by Robert Bethune
//Modified http://www2.cs.uregina.ca/~anima/408/Notes/Timelines/Controlling-the-Display-Rate.htm
//Also https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html
//Main.cpp
//Used for creating a cube and than updating for future project
//Creation Date 1/17/2015
//============================================================================================
#include <iostream>
#include <windows.h>

#include "GL/gl.h"
#include "GL/glut.h"
#include "GameApp.h"

using namespace std;
//--------------------------------------------------------------------------------------------
void idle();
void display();
void update();
void initialize();
void cleanup();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
const unsigned int TARGET_FPS = 60;
const double TIME_PER_FRAME = 1000.0 / TARGET_FPS;
int g_start_time;
int g_current_frame_number;

GameApp* gp_GameApp;
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	gp_GameApp = new GameApp();

	atexit(cleanup);

	initialize();
	return 0;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void initialize()
{
	g_start_time = glutGet(GLUT_ELAPSED_TIME);
	g_current_frame_number = 0;

	gp_GameApp->Init();

	glutInitWindowSize(720, 720);  
	glutInitWindowPosition(50, 50); 
	glutCreateWindow("Rotating Box Test");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glRotated(1, 0, 50,0 );
	glutWireCube(.5);

	glFlush();  
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
