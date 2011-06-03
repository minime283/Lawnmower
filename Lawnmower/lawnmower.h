#ifndef LAWNMOWER_H
#define LAWNMOWER_H
#define CRTDBG_MAP_ALLOC
#include "gamemodeloop.h"
#include "levelloop.h"
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