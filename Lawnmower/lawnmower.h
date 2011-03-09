#ifndef LAWNMOWER_H
#define LAWNMOWER_H
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "grassfield.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <cmath>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_video.h"
#include "SDL_joystick.h"
#include "properties.h"
#include "mower.h"
#include "gamemodeloop.h"
#include "levelloop.h"

//#include "ctexture.h"

using namespace std;

static GLfloat conrotx = 0;
static GLfloat conroty = 0;

static GLfloat Yrot = 0.0f;

static GLfloat eax=0;
static GLfloat eay=0;
static GLfloat eaz=5;
static GLfloat cex=0;
static GLfloat cey=0;
static GLfloat cez=0;
static GLfloat nx=0;
static GLfloat ny=2;
static GLfloat nz=0;
static GLfloat rotX = 36.0f; // Rotate on the X Axis
	static GLfloat rotY = 3.0f; // Rotate on the Y axis
	static GLfloat rotZ = -4.0f; // Rotate around on the Z (based on degrees)
	static GLfloat transX = -6.0; //Translate around the X axis
	static GLfloat transY = -11.0; // Translate around the Y axis
	static GLfloat transZ = -25.0; // Translate around the Z axis
static GLfloat scaleX = 1.0; //Scale X
static GLfloat scaleY = 1.0; //Scale Y
static GLfloat curColor[4]; //color

static bool running = true;
//2D array for developing grass
void runGameLoop(GameModeLoop* myloop);
void initGL();
int main(int argc, char** argv);
#endif