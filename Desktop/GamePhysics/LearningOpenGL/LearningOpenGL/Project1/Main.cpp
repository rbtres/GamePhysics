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

#include "GL/glut.h"
#include "GameApp.h"
#include "InputManager.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix.h"
#include <GL/glui.h>
#include <stdlib.h>
#include <time.h>  

using namespace std;

//--------------------------------------------------------------------------------------------
void idle();
void display();
void update(int mstime);
void initialize();
void cleanup();
void mousePos(int x, int y);
void handleKeyDown(unsigned char key, int x, int y);
void handleKeyUp(unsigned char key, int x, int y);
void reshape(int width, int height);
void handleMouse(int button, int state, int x, int y);
void buttons(int playInt);
void setString(char* s);

//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
const unsigned int TARGET_FPS = 60;
const double TIME_PER_FRAME = 1000.0 / TARGET_FPS;
int g_start_time;
int g_current_frame_number;
int g_rotation_number;
int g_main_win;
int g_delta_time;

static char* currentText;
GameApp* gp_GameApp;
GLUI* gp_Glui;

bool g_isPlaying;

static GLUI_StaticText* text;
static GLUI_StaticText* fpsText;

const int PLAY_ID = 1, STOP_ID = 2, PAUSE_ID = 3;
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	currentText = "";
	g_isPlaying = false;
	gp_GameApp = new GameApp();
	g_rotation_number = 0;
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
	g_main_win = glutCreateWindow("Buttons");

	
	float lightPosition[] = { 100.0, 100.0, 100.0, 0 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	

	gp_GameApp->Init();

	atexit(cleanup);
	glutDisplayFunc(display);
	glutPassiveMotionFunc(mousePos);
	glutKeyboardUpFunc(handleKeyUp);
	
	

	GLUI_Master.set_glutKeyboardFunc(handleKeyDown);
	GLUI_Master.set_glutMouseFunc(handleMouse);
	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutIdleFunc(idle);

	gp_Glui = GLUI_Master.create_glui_subwindow(g_main_win, GLUI_SUBWINDOW_BOTTOM);
	gp_Glui->set_main_gfx_window(g_main_win);
	gp_Glui->add_button("Play", PLAY_ID, buttons);
	gp_Glui->add_button("Stop", STOP_ID, buttons);
	gp_Glui->add_button("Pause", PAUSE_ID, buttons);
	text = gp_Glui->add_statictext(currentText);
	//gp_Glui->add_column(1);
	//fpsText = gp_Glui->add_statictext()
	//gp_Glui->add_column(1);

	

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
		g_delta_time = (int)(end_rendering_time - (g_start_time + (g_current_frame_number ) * TIME_PER_FRAME));
		update(g_delta_time);
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void update(int mstime)
{
	int time = mstime;
	while (time > 1)
	{
		time /= 17;
		g_current_frame_number++;
	}
		
	if (g_isPlaying)
		g_rotation_number++;
	
	glutSetWindow(g_main_win);

	glutPostRedisplay();

	gp_GameApp->Update(mstime, g_isPlaying);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gp_GameApp->Draw();

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
void handleKeyUp(unsigned char key, int x, int y)
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
	GLUI_Master.auto_set_viewport();

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void buttons(int buttonInt)
{
	switch (buttonInt)
	{
	case PAUSE_ID:
		g_isPlaying = false;
		setString("Pause");
		break;
	case PLAY_ID:
		g_isPlaying = true;
		setString("Play");
		break;
	case STOP_ID:
		g_isPlaying = false;
		setString("Stop");
		g_rotation_number = 0;
		gp_GameApp->Reset();
		break;
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void setString(char* s)
{
	text->set_text(s);
}