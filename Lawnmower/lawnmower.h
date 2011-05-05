#ifndef LAWNMOWER_H
#define LAWNMOWER_H
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>
#include "grassfield.h"
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <cmath>
#include "SDL.h"
#include "SDL_opengl.h"
#include "textdisplay.h"
#include "SDL_video.h"
#include "SDL_joystick.h"
#include "properties.h"
#include "mower.h"
#include "gamemodeloop.h"
#include "levelloop.h"

//#include "ctexture.h"

using namespace std;



/**
Run given Gameloop until loop exit
@param GameModeLoop loop to run till exit
**/
void runGameLoop(GameModeLoop* myloop);
/**
Initalizes OpenGL
**/
void initGL();
int main(int argc, char** argv);
#endif