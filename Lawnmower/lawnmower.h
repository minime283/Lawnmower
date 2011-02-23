#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_video.h"
#include "properties.h"
//#include "ctexture.h"

using namespace std;
GLfloat rotX = 36.0f; // Rotate on the X Axis
GLfloat rotY = 3.0f; // Rotate on the Y axis
GLfloat Yrot = 0.0f;

GLfloat rotZ = -4.0f; // Rotate around on the Z (based on degrees)
GLfloat transX = -6.0; //Translate around the X axis
GLfloat transY = -11.0; // Translate around the Y axis
GLfloat transZ = -25.0; // Translate around the Z axis
GLfloat scaleX = 1.0; //Scale X
GLfloat scaleY = 1.0; //Scale Y
GLfloat curColor[4]; //color
const int fieldsize = 16; //Static Size of Field fieldsize X fieldsize
// container for texture arrays
int side_texture; 
int top_texture;
int bot_texture;
int cut_texture;
//Object for texturing class
//ctexture test;
bool running = true;
//Variables for lawnmower position
int rotation=0;
GLfloat lawnmowerup = 0;
GLfloat lawnmowerright = 0;
GLfloat lawnmowerrotation = 0;
//2D array for developing grass
int grasscut[fieldsize+1][fieldsize+1];


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
void specialKey(unsigned char key, int x, int y);
void processMouse(int button, int state, int x, int y);
void processSpecial( SDL_keysym key);
int main(int argc, char** argv);