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

//#include "ctexture.h"

using namespace std;

static GLfloat conrotx = 0;
static GLfloat conroty = 0;
static GLfloat rotX = 36.0f; // Rotate on the X Axis
static GLfloat rotY = 3.0f; // Rotate on the Y axis
static GLfloat Yrot = 0.0f;

static GLfloat rotZ = -4.0f; // Rotate around on the Z (based on degrees)
static GLfloat transX = -6.0; //Translate around the X axis
static GLfloat transY = -11.0; // Translate around the Y axis
static GLfloat transZ = -25.0; // Translate around the Z axis
static GLfloat scaleX = 1.0; //Scale X
static GLfloat scaleY = 1.0; //Scale Y
static GLfloat curColor[4]; //color

// container for texture arrays
static GLuint side_texture; 
static GLuint ttop_texture;
static GLuint bot_texture;
static int cut_texture;
//Object for texturing class
//ctexture test;
static bool running = true;
//2D array for developing grass



//Method for position of grass, and if the grass has been cut
void growGrass();
//Main OpenGL Routing 
void InitGL();
//draws a 1x1 cube. Lawnmower is drawn entirely of these cubes (not including the wheels) (extorted of course)
void drawCube(int size);
//Draws the lawnmower
void lawnmower();
void handleResize(int width, int height);

/*
* Main playing field - Generates a X by Y field of cubes. 
* each smaller cube gets textured so when the playing field 
* increased it doesn't have a stretched squewed look.
*/
void landscape();
//setup the landscape/grass/lawnmower and draw it
void disp();
//Checks to see if collided with sides or grass
void checkCollision();

//handles keyboardup event
//void handleKeyboardUp(SDL_KeyboardEvent Event);
//handles keydown event
//void handleKeyboardDown(SDL_KeyboardEvent Event);
//handles joystick event
//void handleJoystickAxis(SDL_JoyAxisEvent Event);
//checks for events
void checkevents();
int main(int argc, char** argv);
#endif