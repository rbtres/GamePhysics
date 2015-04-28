//============================================================================================
//Create by Robert Bethune
//Worked with Evan, Jake & Alex
//Modified http://www2.cs.uregina.ca/~anima/408/Notes/Timelines/Controlling-the-Display-Rate.htm
//Also https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html
//Mouse Info http://www.zeuscmd.com/tutorials/glut/03-MouseInput.php
//Main.cpp
//Used for creating a cube and than updating for future project
//holds most of opengl linkers.
//Not as clean as I would like. Does more than it should
//however with time restraints and problems this is currently the method I had time to implement
//Creation Date 1/17/2015
//============================================================================================
#include <iostream>
#include <windows.h>

#include "GL/glut.h"
#include "GameApp.h"
#include "InputManager.h"
#include "PhysicsObject.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix.h"
#include <GL/glui.h>
#include <stdlib.h>
#include <time.h>  
#include "ImageHandler.h"

using namespace std;
//--------------------------------------------------------------------------------------------
void idle();
void display();
void update(float msTime);
void initialize();
void cleanup();
void mousePos(int x, int y);
void handleKeyDown(unsigned char key, int x, int y);
void handleKeyUp(unsigned char key, int x, int y);
void reshape(int width, int height);
void handleMouse(int button, int state, int x, int y);
void buttons(int playInt);
void setString(char* s);
void setPlanetText(char* s);
void setFPSText(const char * s);
void setSpeedText(const char* s);
void setVel(const char* s);
void setAcc(const char* s);
void setMass(const char* s);
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
ImageHandler* Handler;
bool g_isPlaying;

static GLUI_StaticText* text;
static GLUI_StaticText* planetText;
static GLUI_StaticText* fpsText;
static GLUI_StaticText* DaysPerSecond;
static GLUI_StaticText* CurrentVel;
static GLUI_StaticText* CurrentMass;
static GLUI_StaticText* CurrentAcc;

PhysicsObject* currentObject;

const int PLAY_ID = 1, STOP_ID = 2, PAUSE_ID = 3;
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	srand((unsigned)time(NULL));
	gp_GameApp = new GameApp();
	glutInit(&argc, argv);
	currentText = "";
	g_isPlaying = false;

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


	float lightPosition[] = { -2, 0, 0, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_LIGHTING); //enable the lighting
	float global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	Handler = ImageHandler::GetInstance();
	Handler->AddImage("snake.jpg", "snake");

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
	gp_Glui->add_column(1);
	fpsText = gp_Glui->add_statictext("FPS: 60");
	gp_Glui->add_statictext("Rods, Cables, and Spring Test");
	gp_Glui->add_column(1);
	planetText = gp_Glui->add_statictext("None");
	//CurrentVel = gp_Glui->add_statictext("");
	CurrentMass = gp_Glui->add_statictext("Contact knows how to detect Collision up to box to box");
	gp_Glui->add_statictext("However resolve is not in so it just falls");
	gp_Glui->add_statictext("WASD to move camera");
	gp_Glui->add_statictext("Gravity force generator for rigid body in the code");


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
		g_delta_time = (int)(end_rendering_time - (g_start_time + (g_current_frame_number)* TIME_PER_FRAME));
		update((float)g_delta_time);
		int x = 1000 / g_delta_time;
		string d = to_string(x);
		string c = "Fps: ";
		string f = c + d;
		const char* s = f.c_str();
		setFPSText(s);


	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void update(float msTime)
{
	float time = msTime;
	while (time > 1)
	{
		time /= 17;
		g_current_frame_number++;
	}

	if (g_isPlaying)
		g_rotation_number++;

	glutSetWindow(g_main_win);

	glutPostRedisplay();

	gp_GameApp->Update(msTime, g_isPlaying);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gp_GameApp->Draw();

	glutSwapBuffers();
	//Sending this into the gp_gameapp and will update by the actuall 
	//input manager / camera hybrid class.
	switch (gp_GameApp->p_InputManager->GetCurrentPlanet())
	{
	case -1: setPlanetText("Rigid Body Sphere falling due to gravity Gen");
		break;

	}
	int x = gp_GameApp->p_InputManager->GetCurrentPlanet();
	if (x >= 0)
	{
		/*
		Vector3D v = currentObject->getAcc();
		string x = to_string(v.X * 1000000000);
		string y = to_string(v.Y * 1000000000);
		string z = to_string(v.Z * 1000000000);
		string c = " , ";
		string d = "Acc = (";
		string m = ")";
		string f = d + x + c + y + c + z + m;
		const char* acc = f.c_str();
		setAcc(acc);
		v = currentObject->getVel();
		x = to_string(v.X * 1000000000);
		y = to_string(v.Y * 1000000000);
		z = to_string(v.Z * 1000000000);
		d = "Vel = (";
		f = d + x + c + y + c + z + m;
		const char* vel = f.c_str();
		setVel(vel);
		*/
		std::string d = "Mass = ";
		float xx = 10;
		std::string y = to_string(xx);
		std::string f = d + y;
		const char* mass = f.c_str();
		setMass(mass);

	}
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
	gp_GameApp->HandleKeyDown(key);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void handleMouse(int button, int state, int x, int y)
{
	gp_GameApp->HandleMouseDown(Vector2D(button, state), Vector2D(x, y));
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
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void setPlanetText(char* s)
{
	planetText->set_text(s);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void setFPSText(const char* s)
{
	fpsText->set_text(s);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void setSpeedText(const char* s)
{
	//DaysPerSecond->set_text("WASD to add force in a direction E to add force up");
}
//--------------------------------------------------------------------------------------------
void setVel(const char* s)
{
	//CurrentVel->set_text(s);
}
void setAcc(const char* s)
{
	//CurrentAcc->set_text(s);
}
void setMass(const char* s)
{
	CurrentMass->set_text(s);
}
void setPlanetText(const char* vel, const char* acc, const char* mass)
{
	//CurrentVel->set_text(vel);
	//CurrentAcc->set_text(acc);
	CurrentMass->set_text(mass);
}